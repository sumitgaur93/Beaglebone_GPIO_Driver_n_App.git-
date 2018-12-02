#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

typedef struct {int num; int val;} gpio;
gpio gp;
gpio * gpio_ptr = &gp;

int8_t kernel_msg[1024];
int main()
{
        int fd;
        printf("*********************************\n");
        printf("*********GPIO Application*******\n");

        fd = open("/dev/etx_device", O_RDWR);
        if(fd < 0) {
                printf("Cannot open device file...\n");
                return 0;
        }

        while(1) {
                printf("****Please Enter the Option******\n");
                printf("        1. Write               \n");
                printf("        2. Read                 \n");
                printf("        3. Exit                 \n");
                printf("*********************************\n");
                scanf(" %c", &option);
                printf("Your Option = %c\n", option);

                switch(option) {
                        case '1':
                                printf("Select the GPIO :");
                                scanf("  %d", &gpio_ptr->num);
                                write(fd, gpio_ptr, sizeof(gpio));
                                read(fd, kernel_msg, sizeof(kernel_msg));
                                if(!(strcmp(kernel_msg,"invalid GPIO Please see the Boad Pinout")))
                                  {
                                    puts(kernel_msg);
                                    break;
                                  }
                                puts(kernel_msg);
                                printf("Select the Value :");
                                scanf("  %d", &gpio_ptr->val);
                                write(fd, gpio_ptr, sizeof(gpio));
                                printf("Data Writing ...");
                                printf("Done!\n");
                                break;
                        case '2':
                                printf("Select the GPIO :");
                                scanf("  %d", &gpio_ptr->num);
                                write(fd, gpio_ptr, sizeof(gpio));
                                read(fd, kernel_msg, sizeof(kernel_msg));
                                if(!(strcmp(kernel_msg,"invalid GPIO Please see the Boad Pinout")))
                                {
                                  puts(kernel_msg);
                                  break;
                                }
                                puts(kernel_msg);
                                printf("Data Reading ...");
                                read(fd, gpio_ptr, sizeof(gpio));
                                printf("Done!\n\n");
                                printf("GPIO = %d\n\n",gpio_ptr->val);
                                break;
                        case '3':
                                close(fd);
                                exit(1);
                                break;
                        default:
                                printf("Enter Valid option = %c\n",option);
                                break;
                }
        }
        close(fd);
}
