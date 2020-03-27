#include<curl/curl.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#include<string.h>
#define BUFFER_SIZE 1000
struct data{
    char name[20];
    char t_case[6];
    char n_case[5];
    char t_deaths[5];
    char n_deaths[4];
};
struct data top[10];
struct data ind;
int top10(){
     //data extraction
    FILE * fp1;
    fp1=fopen("data.html","rb");
    char a[500];
    // puts(a); //test
    char tbody[50]="<tbody>";
    while(fgets(a,500,fp1)!=NULL){
        if(strstr(a,tbody)!=NULL){
            break;
        }
    }
    // printf("the final line is --> %s\n",a); //test for finding line containing <tbody>
    printf("\n\nTOP 10 COUNTRIES : \n\n");
    printf("|sr| country\t| total cases\t| new cases\t| total deaths\t| new deaths |\n");
    int c=1;
    while(c<=10){
        printf("--------------------------------------------------------------------------------\n");
        // printf("%d\n",c);
        fgets(a,500,fp1); //for <tr>
        fgets(a,500,fp1); //for countryname
        int x=0,y=0;
        while(a[x++]!='>');
        while(a[x++]!='>');
        while(a[x]!='<'){
            top[c].name[y++]=a[x++];
        }
        printf("|%d | %s \t",(c),top[c].name);//test to print the country's name
        // printf("--------------------------------------------------------------------------------\n");

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
        printf("| %s \t",top[c].t_case);// test to print t_case

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
        printf("| %s \t",top[c].n_case);//test to print n_case

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
        printf("| %s \t",top[c].t_deaths);//test to print t_deaths

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
        printf("| %s       |\n",top[c].n_deaths);//test to print n_deaths

        //for skipping the next few lines whos data isnt needed
        // fgets(a,500,fp1);
        char tr[50]="</tr>";
        while(fgets(a,500,fp1)!=NULL){
            if(strstr(a,tr)!=NULL){
                break;
            }
        }
        c++;
        printf("--------------------------------------------------------------------------------\n");
        // printf("\n");
    }
    fclose(fp1);  
    return 0;
}
int ind_data(){
    //data extraction for india
    FILE * fp1;
    fp1=fopen("data.html","r+b");
    char a[500];
    fgets(a,500,fp1);
    // puts(a);
    int q=0;
    //skipping to the line where india will be found
    int w=0;
    while(w++<1084){
        fgets(a,500,fp1);
    }
    // printf("the final line is --> %s\n",a); //test
    int p1=0;//pointer for india start
    int fc='1';//pointer of the cursor initialized to a random value
    while(fc++!=EOF){
        fc=fgetc(fp1);
        fseek(fp1,-2,SEEK_CUR);
        fgets(a,500,fp1);//<tr>
        fgets(a,500,fp1);//country name
        int p=0;
        while(a[p++]!='>');//<td>
        //if theres no link for india
            if(a[p]=='I'&&a[p+1]=='n'&&a[p+2]=='d'&&a[p+3]=='i'&&a[p+4]=='a'){
                p1=p;
                break;
            }
        while(a[p++]!='>');//a
          // in case a link is added
            if(a[p]=='I'&&a[p+1]=='n'&&a[p+2]=='d'&&a[p+3]=='i'&&a[p+4]=='a'){
                p1=p;
                break;
            }
    }
    // printf("the final line is --> %s\n",a); //test
    int xi=0;
    while(a[p1]!='<'){
        ind.name[xi++]=a[p1++];
    }
    printf("--------------------------------------------------------------------------------\n");
    printf("%s \n",ind.name);
    printf("--------------------------------------------------------------------------------\n");
    //t_case in india
    int xitc=0,yitc=0;
    fgets(a,500,fp1);
    while(a[xitc++]!='>');
    while(a[xitc]!='<'){
        ind.t_case[yitc++]=a[xitc++];
    }
    printf("total cases --> %s \n",ind.t_case);
    //for n_case in india
    int xinc=0,yinc=0;
    fgets(a,500,fp1);
    while(a[xinc++]!='>');
    while(a[xinc]!='<'){
        ind.n_case[yinc++]=a[xinc++];
    }
    printf("new cases --> %s \n",ind.n_case);
    //for total deaths in india
    int xitd=0,yitd=0;
    fgets(a,500,fp1);
    while(a[xitd++]!='>');
    while(a[xitd]!='<'){
        ind.t_deaths[yitd++]=a[xitd++];
    }
    printf("total deaths --> %s \n",ind.t_deaths);
    //for n_deaths in india
    int xind=0,yind=0;
    fgets(a,500,fp1);
    while(a[xind++]!='>');
    while(a[xind]!='<'){
        ind.n_deaths[yind++]=a[xind++];
    }
    printf("new deaths --> %s \n",ind.n_deaths);
    printf("--------------------------------------------------------------------------------\n");
    return 0;
}
int print_menu(){
    int menu;
    printf("\n\nWELCOME TO TRACK-KARUNA\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("\t press : \n");
    printf("1. GLOBAL STATUS\n2. INDIA'S STATUS\n3. QUIT\n");
    scanf("%d ",&menu);
    printf("--------------------------------------------------------------------------------\n");
    return menu;
}
int main(){
    //file download 
    CURL *curl;
    FILE *fp;
    int result;
    fp=fopen("data.html","wb");
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,"https://www.worldometers.info/coronavirus/");
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result=curl_easy_perform(curl);

    if(result==CURLE_OK){
        printf("\n");
    }
    else{
        printf("error %s \n",curl_easy_strerror(result));
    }
    fclose(fp);
    curl_easy_cleanup(curl);
    int menu;
    while(menu!=3){
        menu=print_menu();
    switch(menu){
        case 1: top10();
            break;
        case 2: ind_data();
            break;
    }
    }
    remove("data.html"); //to delete the file
    return 0;
}