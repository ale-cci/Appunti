/* Corradi Alessandro - 284026 */
#ifndef __UTILS_H__
#define __UTILS_H__

#define pprintf(msg, ...) printf("\e[0;%dm [ %5d ] " msg "\e[0m", pcolor(), getpid(), ##__VA_ARGS__);

/*
    'usage': Requires implementation
    Called when 'require' condition != 0
*/
void usage(FILE* fp, const char* arg0);


/* 'die': perror(msg) + exit(errno) */
void die(const char* msg);


/* 'require': Assure that condition requested is respected, otherwise exit */
void require(int cond, const char* errmsg, const char* arg0);

/* 'pcolor': Unique process color */
int pcolor();

#endif // __UTILS_H__
