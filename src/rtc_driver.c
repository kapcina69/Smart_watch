#include "rtc_driver.h"
#include <zephyr/sys/printk.h>
#include <time.h>
#include <stdio.h>
#include "bmi160.h"

static const struct device *rtc_dev = DEVICE_DT_GET(DT_NODELABEL(rtc0));

int rtc_init(void)
{
    if (!device_is_ready(rtc_dev)) {
        printk("RTC device not ready\n");
        return -ENODEV;
    }

    int ret = counter_start(rtc_dev);
    if (ret != 0) {
        printk("Failed to start counter: %d\n", ret);
        return ret;
    }

    printk("RTC initialized successfully\n");
    return 0;
}



void rtc_set_initial_time(const char *data)
{
    if (data == NULL) {
        printk("Error: data is NULL\n");
        return;
    }

    if (strlen(data) < 19) {  // Proveri da li string ima minimalnu duzinu "YYYY-MM-DD HH:MM:SS"
        printk("Error: Invalid data length\n");
        return;
    }

    struct tm tm_time = {0};
    int scanned = sscanf(data, "%d-%d-%d %d:%d:%d",
                          &tm_time.tm_year,
                          &tm_time.tm_mon,
                          &tm_time.tm_mday,
                          &tm_time.tm_hour,
                          &tm_time.tm_min,
                          &tm_time.tm_sec);

    if (scanned != 6) {
        printk("Error: Failed to parse data\n");
        return;
    }

    tm_time.tm_year -= 1900;  // Godina je broj godina od 1900.
    tm_time.tm_mon -= 1;      // Mesec je 0-based (januar je 0, februar je 1,...)

    time_t new_time = mktime(&tm_time);
    struct timespec ts = {.tv_sec = new_time};

    if (clock_settime(CLOCK_REALTIME, &ts) < 0) {
        printk("Failed to set initial time\n");
    } else {
        printk("Initial time set to: %04d-%02d-%02d %02d:%02d:%02d\n",
               tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
               tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
    }
}



void rtc_update_time_label(lv_obj_t *time_label, lv_obj_t *date_label,lv_obj_t *short_time_label)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) < 0) {
        printk("Failed to get time\n");
        return;
    }

    struct tm *timeinfo = gmtime(&ts.tv_sec);
    if (timeinfo == NULL) {
        printk("Failed to convert time\n");
        return;
    }

    static const char *weekday_names[] = {
        "nedelja", "pon", "utorak", "sreda", "cetvrtak", "petak", "subota"
    };

    static const char *month_names[] = {
        "jan", "feb", "mar", "apr", "maj", "jun",
        "jul", "avg", "sep", "okt", "nov", "dec"
    };

    char time_buf[16];
    char short_time_buf[16];
    char date_buf[32];

    snprintf(time_buf, sizeof(time_buf), "%02d:%02d:%02d",
             timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
    snprintf(short_time_buf, sizeof(short_time_buf), "%02d:%02d",
                timeinfo->tm_hour, timeinfo->tm_min);
    lv_label_set_text(short_time_label, short_time_buf);
    if(time_buf[0] == '0' && time_buf[1] == '0' && time_buf[3] == '0' && time_buf[4] == '0' && time_buf[6] == '0' && time_buf[7] == '0') {
        bmi160_reset_step_counter();
    }

    snprintf(date_buf, sizeof(date_buf), "%s, %02d %s %04d",
             weekday_names[timeinfo->tm_wday],
             timeinfo->tm_mday,
             month_names[timeinfo->tm_mon],
             timeinfo->tm_year + 1900);


    lv_label_set_text(time_label, time_buf);


    lv_label_set_text(date_label, date_buf);
  

    printk("Vreme: %s | Datum: %s\n", time_buf, date_buf);
}

#include <time.h>

char time_labels[3][6] = {"--:--", "--:--", "--:--"};
int inthr = 0;  // Globalna promenljiva - signal koji setuješ
void update_minute_labels_and_signal(void) {
    static int prev_minute = -1;
    const size_t time_label_size = sizeof(time_labels[0]);

    // Dohvatanje trenutnog vremena
    struct timespec ts;
    if (clock_gettime(CLOCK_REALTIME, &ts) < 0) {
        printk("Greška pri dohvatanju vremena: %d\n", errno);
        inthr = 0;
        return;
    }

    // Konverzija vremena
    struct tm *timeinfo = gmtime(&ts.tv_sec);
    if (!timeinfo) {
        printk("Greška pri konverziji vremena\n");
        inthr = 0;
        return;
    }

    // Provera promene minuta
    if (timeinfo->tm_min == prev_minute) {
        inthr = 0;
        return;
    }

    // Ažuriranje prethodnog minuta
    prev_minute = timeinfo->tm_min;

    // Priprema novog vremenskog stringa
    char new_time_label[6];
    int len = snprintf(new_time_label, sizeof(new_time_label), "%02d:%02d",
                      timeinfo->tm_hour, timeinfo->tm_min);
    
    if (len != 5 || new_time_label[5] != '\0') {
        printk("Greška pri formatiranju vremena\n");
        inthr = 0;
        return;
    }

    // Rotacija labela unazad
    for (int i = 0; i < 2; i++) {
        strncpy(time_labels[i], time_labels[i+1], time_label_size);
        time_labels[i][time_label_size - 1] = '\0';
    }

    // Dodavanje nove labele
    strncpy(time_labels[2], new_time_label, time_label_size);
    time_labels[2][time_label_size - 1] = '\0';

    // Postavljanje signala
    inthr = 1;

    // Logovanje promene (samo za debug)
    printk("Ažurirane vremenske labele: [%s][%s][%s]\n",
           time_labels[0], time_labels[1], time_labels[2]);
}