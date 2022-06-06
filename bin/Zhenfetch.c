#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define ANSI_BACKGROUND_RED     "\x1b[41m"
#define ANSI_BACKGROUND_GREEN   "\x1b[42m"
#define ANSI_BACKGROUND_YELLOW  "\x1b[43m"
#define ANSI_BACKGROUND_BLUE    "\x1b[44m"
#define ANSI_BACKGROUND_MAGENTA "\x1b[45m"
#define ANSI_BACKGROUND_CYAN    "\x1b[46m"

 //Arch
/*
char image[][100] = {
"        /\\         ",
"       /  \\        ",
"      /\\   \\       ",
"     /  __  \\      ",
"    /  (  )  \\     ",
"   / __|  |__\\\\    ",
"  /.\'        \'.\\   ",
}; 
*/

// Default
char image[][100] = {
"⣿⡟⠙⠛⠋⠩⠭⣉⡛⢛⠫⠭⠄⠒⠄⠄⠄⠈⠉⠛⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿",
"⣿⡇⠄⠄⠄⠄⣠⠖⠋⣀⡤⠄⠒⠄⠄⠄⠄⠄⠄⠄⠄⠄⣈⡭⠭⠄⠄⠄⠉⠙",
"⣿⡇⠄⠄⢀⣞⣡⠴⠚⠁⠄⠄⢀⠠⠄⠄⠄⠄⠄⠄⠄⠉⠄⠄⠄⠄⠄⠄⠄⠄",
"⣿⡇⠄⡴⠁⡜⣵⢗⢀⠄⢠⡔⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄",
"⣿⡇⡜⠄⡜⠄⠄⠄⠉⣠⠋⠠⠄⢀⡄⠄⠄⣠⣆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢸",
"⣿⠸⠄⡼⠄⠄⠄⠄⢰⠁⠄⠄⠄⠈⣀⣠⣬⣭⣛⠄⠁⠄⡄⠄⠄⠄⠄⠄⢀⣿",
"⣏⠄⢀⠁⠄⠄⠄⠄⠇⢀⣠⣴⣶⣿⣿⣿⣿⣿⣿⡇⠄⠄⡇⠄⠄⠄⠄⢀⣾⣿",
"⣿⣸⠈⠄⠄⠰⠾⠴⢾⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⢁⣾⢀⠁⠄⠄⠄⢠⢸⣿⣿",
"⣿⣿⣆⠄⠆⠄⣦⣶⣦⣌⣿⣿⣿⣿⣷⣋⣀⣈⠙⠛⡛⠌⠄⠄⠄⠄⢸⢸⣿⣿",
"⣿⣿⣿⠄⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠇⠈⠄⠄⠄⠄⠄⠈⢸⣿⣿",
"⣿⣿⣿⠄⠄⠄⠘⣿⣿⣿⡆⢀⣈⣉⢉⣿⣿⣯⣄⡄⠄⠄⠄⠄⠄⠄⠄⠈⣿⣿",
"⣿⣿⡟⡜⠄⠄⠄⠄⠙⠿⣿⣧⣽⣍⣾⣿⠿⠛⠁⠄⠄⠄⠄⠄⠄⠄⠄⠃⢿⣿",
"⣿⡿⠰⠄⠄⠄⠄⠄⠄⠄⠄⠈⠉⠩⠔⠒⠉⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠐⠘⣿",
"⣿⠃⠃⠄⠄⠄⠄⠄⠄⣀⢀⠄⠄⡀⡀⢀⣤⣴⣤⣤⣀⣀⠄⠄⠄⠄⠄⠄⠁⢹"
};

/*
// The Only Thing I Know For Real
char image[][100] = {
"               ⣠⣴⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⢀⣀⣀⣀⣤⣤⣤⣀⣀⣀⣀⣀⣀⣿⣿⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀ ",
"⠀⠘⠛⠛⢻⣿⣿⠿⢻⣿⣿⣿⣿⣿⣿⣿⣿⡿⣷⣤⣤⠀⠀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠹⣿⣿⣄⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣦⡈⠉⠁⠀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⡀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⢺⣿⣿⣿⡿⠻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⣦⣄⣀⣠⣤⡄",
"⠀⠀⠀⠀⠀⠀⠈⠉⠉⠀⠀⢻⣿⣿⣿⣿⣿⣿⠁⣉⣽⣿⣿⡿⢿⣿⣿⡷⠂",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣏⠉⠁⠀⠈⠁⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⣿⣿⣿⣿⣿⣿⣯⠛⠁⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⣾⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⠻⣿⣿⣿⣿⠄⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⠏⣰⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀ ",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⣿⣿⣿⠀⢿⣿⣿⣿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⠀⢸⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⡿⠁⠀⣾⣿⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡇⠀⢸⣿⣿⣿⣶⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠉⠉⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀",
"⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡿⠀				  "
};
*/

int height = sizeof(image) / sizeof(image[0]);
int min_width = 75;

char img_color[] = ANSI_COLOR_RESET;
char hightlight_color[] = ANSI_COLOR_CYAN;
struct winsize win;


void getOs(char *);
void getKernel(char *);
void getUptime(char *);
void getDE(char *);
void getUser(char *);
void getShell(char *);
void drawLine();
void getColors(char *);

int main() {
	ioctl(0, TIOCGWINSZ, &win);

	char osName[30];
	char kernelVersion[30];
	char uptime[30];
	char DE[30];
	char user[60];
	char shell[30];
	char colors[60];


	getOs(osName);
	getKernel(kernelVersion);
	getUptime(uptime);
	getDE(DE);
	getUser(user);
	getShell(shell);
	getColors(colors);

	char format[] = "%s%s%s:\t\t%s";	
	char os_format[60], kernel_format[60], uptime_format[60], de_format[60], shell_format[60], user_format[60];
	sprintf(os_format,format,hightlight_color,"OS",ANSI_COLOR_RESET,osName);
	sprintf(kernel_format,format,hightlight_color,"KERNEL",ANSI_COLOR_RESET,kernelVersion);
	sprintf(uptime_format,format,hightlight_color,"UPTIME",ANSI_COLOR_RESET,uptime);
	sprintf(de_format,format,hightlight_color,"DE",ANSI_COLOR_RESET,DE);
	sprintf(shell_format,format,hightlight_color,"SHELL",ANSI_COLOR_RESET,shell);

	int info_length = 7;

	char info[info_length][60];

	strcpy(info[0],user);
	strcpy(info[1],os_format);
	strcpy(info[2],kernel_format);
	strcpy(info[3],uptime_format);
	strcpy(info[4],de_format);
	strcpy(info[5],shell_format);
	strcpy(info[6],colors);


	int center = (height - info_length) / 2;

	int i_of_info = 0;

	if(win.ws_col < min_width) height = info_length;

	for(int i = 0; i < height; i++) {
		drawLine(i);
		if(i >= center && i_of_info < info_length || info_length == height) {
			printf("%s",info[i_of_info]);
			i_of_info+=1;
		}
		printf("\n");
	}

	return 0;
};

void getOs(char *var) {
	char text[30];
	FILE* f = fopen("/etc/os-release","r");
	if(f == NULL) {
		strcpy(var,"Unknown");
		return;
	}
	fgets(text,30,f);

	bool splited = false;
	char name[30];
	int i2 = 0;

	for(int i = 0; i < 30; i++) {

		if(text[i]=='=') {
			splited = true;
			continue;
		}

		if(splited) {
			if(text[i] == '"' || text[i] == '\n') continue;
			name[i2] = text[i];
			i2+=1;
		};
	}

	fclose(f);

	strcpy(var,name);
};

void getKernel(char *var) {
	char text[30];
	FILE* f = fopen("/proc/version","r");
	if(f == NULL) {
		strcpy(var,"Unknown");
		return;
	}
	fgets(text,30,f);

	char version[30];

	for(int i = 0; i < 30; i++) {
		if(text[i] == '(') {
			break;
		}

		version[i] = text[i];
	}

	fclose(f);

	strcpy(var,version);
}

void getUptime(char *var) {
	char text[30];
	FILE* f = fopen("/proc/uptime","r");

	if(f == NULL) {
		strcpy(var,"Unknown");
		return;
	}

	float time;
	int hours, minutes;

	fgets(text,30,f);

	time = atof(text) / 3600;

	hours = (int)time;
	minutes = (time - hours) * 60;

	char format[] = "%i hours, %i minutes";
	char inf[30];

	sprintf(inf,format,hours,minutes);

	strcpy(var,inf);
	fclose(f);
}


void getDE(char *var) {
	if(getenv("DESKTOP_SESSION") == NULL) {
		strcpy(var,"Unknown");
		return;
	}
	strcpy(var,getenv("DESKTOP_SESSION"));
}

void getUser(char *var) {
	char hostname[30];
	FILE *f = fopen("/etc/hostname","r");
	if(f == NULL) {
		strcpy(var,"Unknown");
		return;
	}
	fgets(hostname,30,f);

	char username[30];
	strcpy(username,getenv("USER"));

	char format[] = "%s%s%s@%s%s%s"; // Username@Hostname
	
	char inf[60];

	sprintf(inf,format,hightlight_color,username,ANSI_COLOR_RESET,hightlight_color,hostname,ANSI_COLOR_RESET);

	for(int i = 0; i < 60; i++) {
		if(inf[i] == '\n') {
			inf[i] = ' ';
		}
	}

	strcpy(var,inf);
	fclose(f);
}

void getShell(char *var) {
	char path[30];
	
	strcpy(path,getenv("SHELL"));
	
	bool end = false;
	char name[30];
	int iname = 0;

	int slashcount = 0;
	for(int i = 0; i < 30; i++ )
		if(path[i] == '/') slashcount++;


	int slashcount2 = 0;
	for(int i = 0; i < 30; i++) {
		
		if(end) {
			name[iname] = path[i];
			iname+=1;
			continue;
		}
		
		if(path[i] == '/') {
			slashcount2++;
			if(slashcount == slashcount2) end = true;
		}
	}

	strcpy(var,name);
}

void drawLine(int line) {

	if(win.ws_col < min_width) return;
	printf("%s%s\t%s",img_color,image[line],ANSI_COLOR_RESET);
}

void getColors(char *var) {
	char temp[10];
	char text[60] = "\t\t";

	char format[] = "\x1b[4%im   ";
	for(int i = 1; i <= 6; i++) {
		sprintf(temp,format,i);
		strcat(text,temp);
	}

	strcat(text,ANSI_COLOR_RESET);
	strcpy(var,text);
}
