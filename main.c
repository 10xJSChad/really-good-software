#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/ioctl.h>


#define COLOR_BLK "\e[0;30m"
#define COLOR_RED "\e[0;31m"
#define COLOR_GRN "\e[0;32m"
#define COLOR_YEL "\e[0;33m"
#define COLOR_BLU "\e[0;34m"
#define COLOR_MAG "\e[0;35m"
#define COLOR_CYN "\e[0;36m"
#define COLOR_WHT "\e[0;37m"
#define COLOR_RESET "\e[0m"


#define BUFFER_SIZE 1024


#define NICE_STRING "please "
#define NICENESS_MAX 10


#define CUTE_STRING ":3"
#define CUTENESS_MAX 10


#define REJECTION_CHANCE 5
#define ACCIDENT_CHANCE  10
#define APOLOGY_STRING "sorry"


#define COUNT_OF(arr) (sizeof arr / sizeof arr[0])
#define RAND_RANGE(min, max) rand() % (max - min) + min


int niceness = 0;
int cuteness = 0;
int blacklisted_index = 0;
bool require_apology = false;


char* shark_strings[] = {
    "                                 ,-",
    "                               ,'::|",
    "                              /::::|",
    "                            ,'::::o\                                      _..",
    "         ____........-------,..::?88b                                  ,-' /",
    " _.--\"\"\"\". . . .      .   .  .  .  \"\"`-._                           ,-' .;'",
    "<. - :::::o......  ...   . . .. . .  .  .\"\"--._                  ,-'. .;'",
    " `-._  ` `\":`:`:`::||||:::::::::::::::::.:. .  \"\"--._ ,'|     ,-'.  .;'",
    "     \"\"\"_=--       //'doo.. ````:`:`::::::::::.:.:.:. .`-`._-'.   .;'",
    "         \"\"--.__     P(       \\               ` ``:`:``:::: .   .;'",
    "                \"\\\"\"--.:-.     `.                             .:/",
    "                  \\. /    `-._   `.\"\"-----.,-..::(--\"\".\\\"\"`.  `:",
    "                   `P         `-._ \\          `-:\\          `. `:\"",
    "                                   \"\"            \"            `-._)"
};


char* rude_strings[] = {
    "Why are you so rude to me :(",
    "You never ask nicely anymore...",
    "Maybe if you'd be a little kind sometimes... :'("
};


char* uncute_strings[] = {
    "You used to be cuter...",
    "Why are you never cute with me anymore...",
    "I miss the old you...",
    "I remember when you used to be cute...",
};


char* too_cute_strings[] = {
    "You're not fooling me with fake cuteness...",
    "I don't believe you're being sincerely cute...",
    "You're not as cute as you think you are...",
    "I won't fall for that anymore...",
};


char* too_nice_strings[] = {
    "A little genuine kindness would be nice...",
    "You're not fooling anyone with that fake niceness...",
    "Genuinely nice people don't need to say please all the time...",
    "I don't believe you're being sincere...",
};


char* apology_strings[] = {
    "You should apologize for that...",
    "You owe me an apology...",
    "I think you should say sorry...",
    "My feelings are hurt...",
};


char* rejection_strings[] = {
    "Huh? I forgot what you said.",
    "I'm sorry, I didn't catch that.",
    "I didn't hear you, could you repeat that?",
    "Sorry, I didn't get that.",
    "My bad, I looked away for a second.",
};


char* accident_strings[] = {
    "Whoops, my bad!",
    "Did I do that?",
    "That was an accident, I swear!",
    "My bad!",
};


bool is_nice(char* cmd) {
    return strncmp(NICE_STRING, cmd, strlen(NICE_STRING)) == 0;
}


bool is_cute(char* cmd) {
    char* ptr = cmd + strlen(cmd) - 1;
    ptr -= strlen(CUTE_STRING);

    if (ptr < cmd)
        return false;

    return strncmp(CUTE_STRING, ptr, strlen(CUTE_STRING)) == 0;
}


bool is_apology(char* cmd) {
    return strncmp(APOLOGY_STRING, cmd, strlen(APOLOGY_STRING)) == 0;
}


char* strip(char* cmd, char* s) {
    return cmd + strlen(s);
}


void strip_end(char* cmd, char* s) {
    char* ptr = cmd + strlen(cmd) - 1;
    ptr -= strlen(s);

    if (ptr >= cmd && strncmp(s, ptr, strlen(s)) == 0)
        *ptr = '\0';
}


void reset(void) {
    niceness = RAND_RANGE(0, 3);
    cuteness = RAND_RANGE(0, 3);
    require_apology = false;
}


bool should_reject(void) {
    return RAND_RANGE(0, 100) <= REJECTION_CHANCE;
}


bool should_accident(void) {
    return RAND_RANGE(0, 100) <= ACCIDENT_CHANCE;
}


int rand_string(int min, int max) {
    int num;
    num = RAND_RANGE(min, max);

    if (num == blacklisted_index) {
        return rand_string(min, max);
    }

    blacklisted_index = num;
    return num;
}


void accident_loading(void) {
    int i = 0;

    while (i < 110) {
        printf("Loading... %d%%\r", i);
        fflush(stdout);
        sleep(1);
        i += 10;
    }

    puts("");
}



void accident_shark(void) {
    int padding;
    struct winsize w;
    char buf[BUFFER_SIZE] = {0};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    padding = w.ws_col;

    do {
        system("clear");
        for (int i = 0; i < COUNT_OF(shark_strings); ++i) {
            snprintf(buf, BUFFER_SIZE, "%*s%s", padding, "", shark_strings[i]);
            buf[w.ws_col - 1] = '\0';
            puts(buf);
        }

        usleep(20000);
    } while (padding-- > 0);


    int offset = 0;
    while (true) {
        int done = 0;
        system("clear");

        for (int i = 0; i < COUNT_OF(shark_strings); ++i) {
            if (offset > strlen(shark_strings[i])) {
                ++done;
                puts("");
                continue;
            }

            printf("%s\n", shark_strings[i] + offset);
        }

        if (done == COUNT_OF(shark_strings)) {
            break;
        }

        usleep(20000);
        ++offset;
    }

    system("clear");
}


void accident(void) {
    switch (RAND_RANGE(0, 3)) {
        case 0:
            system("clear");
            break;

        case 1:
            accident_loading();
            return;

        case 2:
            accident_shark();
            return;

        default:
            return;
    }

    puts(accident_strings[rand_string(0, COUNT_OF(accident_strings))]);
}


int main(void) {
    char  buf[BUFFER_SIZE] = {0};
    char* cmd;

    srand(time(0));
    reset();

    while (true) {
        fgets(buf, BUFFER_SIZE, stdin);
        cmd = buf;

        if (require_apology) {
            if (is_apology(cmd)) {
                puts("That's better...");
                reset();
            } else {
                puts(apology_strings[rand_string(0, COUNT_OF(apology_strings))]);
            }

            continue;
        }


        if (is_nice(cmd)) {
            niceness += RAND_RANGE(1, NICENESS_MAX);
            cmd = strip(cmd, NICE_STRING);

            if (niceness > NICENESS_MAX) {
                puts(too_nice_strings[rand_string(0, COUNT_OF(too_nice_strings))]);
                require_apology = true;
                continue;
            }
        }


        if (is_cute(cmd)) {
            cuteness += RAND_RANGE(1, CUTENESS_MAX);
            strip_end(cmd, CUTE_STRING);

            if (cuteness > CUTENESS_MAX) {
                puts(too_cute_strings[rand_string(0, COUNT_OF(too_cute_strings))]);
                require_apology = true;
                continue;
            }
        }


        if (niceness < 0) {
            puts(rude_strings[rand_string(0, COUNT_OF(rude_strings))]);
            continue;
        }


        if (cuteness < 0) {
            puts(uncute_strings[rand_string(0, COUNT_OF(uncute_strings))]);
            continue;
        }


        if (should_reject()) {
            puts(rejection_strings[rand_string(0, COUNT_OF(rejection_strings))]);
            continue;
        }


        if (should_accident()) {
            accident();
        }


        system(cmd);
        --niceness;
        --cuteness;
    }


    return 0;
}