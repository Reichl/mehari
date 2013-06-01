/* Simple SPIdev example to read the data from an MAX31855 thermocouple amplifier */
 
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
 
#define ARRAY_SIZE(array) sizeof(array)/sizeof(array[0])
 
/* Dataformat:
* D[31:18] These bits contain the signed 14-bit thermocouple temperature value in degrees Celsius * 4.
* D17 Reserved, this bit always reads 0.
* D16 Fault, this bit reads at 1 when any of the SCV, SCG, or OC faults are active. Default value is 0.
* D[15:4] These bits contain the signed 12-bit value of the reference junction temperature in degrees Celsius * 16.
* D3 Reserved, this bit always reads 0.
* D2 This bit is a 1 when the thermocouple is short-circuited to VCC. Default value is 0.
* D1 This bit is a 1 when the thermocouple is short-circuited to GND. Default value is 0.
* D0 This bit is a 1 when the thermocouple is open (no connections). Default value is 0.
*/
 
/* Compile with 'gcc -o spidev-max31855 spidev-max31855.c' */
 
#define FAULT 1
 
#define SCV 4
#define SCG 2
#define OC 1
 
int main(int argc, char **argv)
{
int fd;
int fault, scv, scg, oc;
/* Read 4 bytes from the SPI bus */
char buf[4];
double celsius, internal_celsius;
 
if (argc<2) {
printf("Usage:\n%s [device]\n", argv[0]);
exit(1);
}
fd = open(argv[1], O_RDWR);
if (fd<=0) {
printf("%s: Device %s not found\n", argv[0], argv[1]);
exit(1);
}
 
if (read(fd, buf, ARRAY_SIZE(buf)) != ARRAY_SIZE(buf))
perror("SPI read Error");
close(fd);
 
/* Read the fault bit */
fault = buf[1] & FAULT;
 
/* If the fault bit is set read the fault conditions and print them */
if(fault) {
scv = buf[3] & SCV;
scg = buf[3] & SCG;
oc = buf[3] & OC;
 
printf("Fault detected: scv: %X, scg: %X, oc: %X\n", scv, scg, oc);
} else {
celsius = ( ( buf[0] << 6 ) + ( buf[1] >> 2 ) ) / 4.0;
printf("Thermocouple temperature: %.2f degrees Celsius\n", celsius);
}
 
internal_celsius = ( ( buf[2] << 4) + ( buf[3] >> 4 ) ) / 16.0;
printf("Reference junction temperature: %.4f degrees Celsius\n", internal_celsius);
 
return 0;
}
