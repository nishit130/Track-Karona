#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<string.h>
#define BUFFER_SIZE 1000
int  isEmpty(const char *str);
void removeEmptyLines(FILE *srcFile, FILE *tempFile);
void printFile(FILE *fptr);
int clean(){
    FILE *srcFile;
    FILE *tempFile;
    srcFile  = fopen("data.html", "r");
    tempFile = fopen("remove-blanks.tmp", "w");
    /* Exit if file not opened successfully */
    if (srcFile == NULL || tempFile == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check you have read/write previleges.\n");
        exit(EXIT_FAILURE);
    }
    // printf("\nFile contents before removing all empty lines.\n\n");
    // printFile(srcFile);
    // Move src file pointer to beginning
    rewind(srcFile);
    // Remove empty lines from file.
    removeEmptyLines(srcFile, tempFile);
    /* Close all open files */
    fclose(srcFile);
    fclose(tempFile);
    /* Delete src file and rename temp file as src */
    remove("data.html");
    rename("remove-blanks.tmp", "data.html");
    // printf("\n\n\nFile contents after removing all empty line.\n\n");
    // Open source file and print its contents
    srcFile = fopen("data.html", "r");
    // printFile(srcFile);
    fclose(srcFile);
    return 0;
}
/**
 * Print contents of a file.
 */
void printFile(FILE *fptr)
{
    char ch;
    while((ch = fgetc(fptr)) != EOF)
        putchar(ch);
}
/**
 * Checks, whether a given string is empty or not.
 * A string is empty if it only contains white space
 * characters.
 * 
 * Returns 1 if given string is empty otherwise 0.
 */
int isEmpty(const char *str)
{
    char ch;
    do
    {
        ch = *(str++);
        // Check non whitespace character
        if(ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r' && ch != '\0')
            return 0;
    } while (ch != '\0');
    return 1;
}
/**
 * Function to remove empty lines from a file.
 */
void removeEmptyLines(FILE *srcFile, FILE *tempFile)
{
    char buffer[BUFFER_SIZE];
    while ((fgets(buffer, BUFFER_SIZE, srcFile)) != NULL)
    {
        /* If current line is not empty then write to temporary file */
        if(!isEmpty(buffer))
            fputs(buffer, tempFile);
    }
}
struct data{
    char name[20];
    char t_case[5];
    char n_case[4];
    char t_deaths[4];
    char n_deaths[3];
};
struct data top[10];
int main(int url, char **image){
    //file download 
    CURL *curl;
    FILE *fp;
    int result;
    fp=fopen(image[2],"wb");
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,image[1]);
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result=curl_easy_perform(curl);
    if(result==CURLE_OK){
        printf("TOP 10 COUNTRIES : \n\n");
    }
    else{
        printf("error %s \n",curl_easy_strerror(result));
    }
    fclose(fp);
    curl_easy_cleanup(curl);
    //file cleaning
    clean();
    //data extraction
    FILE * fp1;
    fp1=fopen("data.html","rb");
    char a[500];
    fgets(a,500,fp1);
    // puts(a);
    int q=0;
    // while(q!=EOF){
    //     fgets(a,500,fp1);
    //     q=fgetc(fp1);
    //     // int w=0;
    //     // while(a[w++]!='<');
    //     puts(a);
    //     if(a[18]=='<'&&a[19]=='t'&&a[20]=='b'&&a[21]=='o'&&a[22]=='d'&&a[23]=='y'&&a[24]=='>'){
    //         break;
    //     }
    // }
    int w=0;
    while(w++<1084){
        fgets(a,500,fp1);
    }
    // printf("the final line is --> %s\n",a); //test
    int c=1;
    while(c<=10){
        printf("%d\n",c);
        fgets(a,500,fp1); //for <tr>
        fgets(a,500,fp1); //for countryname
        int x=0,y=0;
        while(a[x++]!='>');
        while(a[x++]!='>');
        while(a[x]!='<'){
            top[c].name[y++]=a[x++];
        }
        printf("country --> %s \n",top[c].name);

        //for t_cases
        fgets(a,500,fp1);
        int xtc=0,ytc=0;
        while(a[xtc++]!='>');
        while(a[xtc]!='<'){
            if(a[xtc]==' '){
                break;
                }
            top[c].t_case[ytc++]=a[xtc++];
        }
        printf("total cases --> %s \n",top[c].t_case);

        //for n_case
        fgets(a,500,fp1);
        int xnc=0,ync=0;
        while(a[xnc++]!='>');
        while(a[xnc]!='<'){
            if(a[xnc]==' '){
                break;
            }
            top[c].n_case[ync++]=a[xnc++];
        }
        printf("new cases --> %s \n",top[c].n_case);

        //for t_deaths
        fgets(a,500,fp1);
        int xtd=0,ytd=0;
        while(a[xtd++]!='>');
        while(a[xtd]!='<'){
            if(a[xtd]==' '){
                break;
            }
            top[c].t_deaths[ytd++]=a[xtd++];
        }
        printf("total deaths --> %s \n",top[c].t_deaths);

        fgets(a,500,fp1); // for an extra blank line
        //for n_deaths
        fgets(a,500,fp1);
        int xnd=0,ynd=0;
        while(a[xnd++]!='>');
        while(a[xnd]!='<'){
            if(a[xnd]==' '){
                break;
            }
            top[c].n_deaths[ynd++]=a[xnd++];
        }
        printf("new deaths --> %s \n",top[c].n_deaths);

        //for skipping the next 6 lines whos data isnt needed
        int ign=0;
        while(ign++<4){
            fgets(a,500,fp1);
        }
        c++;
        printf("\n");
    }
    fclose(fp1);  
    return 0;
}