#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/inotify.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include<libnotify/notification.h>
#include <libnotify/notify.h>

#define ERROR -1
#define BUFFER_SIZE 1024

int send_notif(const char *appname, const char *title, const char * body);

void send_notification(char *msg){
    send_notif("File-Access-Monitor", "ALERT!", msg);
}



int main(int argc, char *argv[]) {
    char *filepath = argv[1];
    char buffer[BUFFER_SIZE];

    if(argc!=2){
        printf("[ERROR] INPUT ERROR\n");
        return -2;
    }

    // Initialize inotify
    int inotify_fd = inotify_init();
    if (inotify_fd < 0) {
        fprintf(stderr, "Error initializing inotify: %s\n", strerror(errno));
        return -1;
    }

    // Add a watch on the specified file
    int watch_desc = inotify_add_watch(inotify_fd, filepath, IN_ALL_EVENTS);
    if (watch_desc < 0) {
        fprintf(stderr, "Error adding watch on %s: %s\n", filepath, strerror(errno));
        close(inotify_fd);
        return -1;
    }

    printf("Monitoring file: %s\n", filepath);

    while (1) {
        // Read events from inotify file descriptor
        ssize_t len = read(inotify_fd, buffer, sizeof(buffer));
        if (len == -1) {
            if (errno == EINTR) continue; // Interrupted by signal, retry
            fprintf(stderr, "[ERROR] Read error: %s\n", strerror(errno));
            break;
        }

        // Process events
        int i = 0;
        while (i < len) {
            struct inotify_event *event = (struct inotify_event *)&buffer[i];

            //printf("Event on watch descriptor %d: ", event->wd);
            if (event->mask & IN_MODIFY) {
                send_notification("File modified.\n");
            }
            if (event->mask & IN_CREATE) {
                send_notification("File created");
            }
            if (event->mask & IN_DELETE) {
                send_notification("File deleted\n");
            }
            if (event->mask & IN_OPEN) {
                send_notification("File opened.\n");
            }
            if (event->mask & IN_ACCESS) {
                send_notification("File accessed.\n");
            }


            i += sizeof(struct inotify_event) + event->len;
        }
    }

    // Clean up
    inotify_rm_watch(inotify_fd, watch_desc);
    close(inotify_fd);

    return 0;
}



int send_notif(const char *appname, const char *title, const char * body){
    if(!notify_init(appname)){
        return ERROR;
    }

    NotifyNotification *notif = notify_notification_new(title, body, ""); // figure the image later
    if (!notify_notification_show(notif, NULL)) {
        notify_uninit();
        return ERROR;
    }
    notify_uninit();
    return 0;
}