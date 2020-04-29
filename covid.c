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
    char tbody[505]="<td style=\"display:none\" data-continent=\"all\">All</td>";
    while(fgets(a,500,fp1)!=NULL){
        if(strstr(a,tbody)!=NULL){
            break;
        }
    }
    // printf("the final line is --> %s\n",a); //test for finding line containing <tbody>
    printf("\n\nTOP 10 COUNTRIES : \n\n");
    printf("|sr|\tcountry\t\t| total cases | new cases | total deaths | new deaths |\n");
    int c=1;
    fgets(a,500,fp1);
    while(c<=10){
        // printf("--------------------------------------------------------------------------------\n");
        // printf("%d\n",c);
        fgets(a,500,fp1); //for <tr>
        fgets(a,500,fp1); //for countryname
        int x=0,y=0;
        while(a[x++]!='>');
        while(a[x++]!='>');
        while(a[x]!='<'){
            top[c].name[y++]=a[x++];
        }
	if(c!=0)
        	printf(" %2d   %-20s",(c),top[c].name);//test to print the country's name
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
	if(c!=0)
        	printf("%-13s ",top[c].t_case);// test to print t_case

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
	if(c!=0)
	        printf("  %-11s ",top[c].n_case);//test to print n_case

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
	if(c!=0)
	        printf("  %-14s \t",top[c].t_deaths);//test to print t_deaths

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
	if(c!=0)
        	printf("  %-12s\n",top[c].n_deaths);//test to print n_deaths

        //for skipping the next few lines whos data isnt needed
        // fgets(a,500,fp1);
        char tr[50]="</tr>";
        while(fgets(a,500,fp1)!=NULL){
            if(strstr(a,tr)!=NULL){
                break;
            }
        }
        c++;
        // printf("--------------------------------------------------------------------------------\n");
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
    char q[50]="<tbody>";
    //skipping to the line where india will be found
    char w[50]="India";
    while(fgets(a,500,fp1)!=NULL){
        if(strstr(a,q)!=NULL){
            break;
        }
    }
    while(fgets(a,500,fp1)!=NULL){
        if(strstr(a,w)!=NULL){
            break;
        }
    }
        int p=0;
        while(a[p++]!='>');//<td>
        while(a[p++]!='>');//<a href>
    // printf("the final line is --> %s\n",a); //test
    int xi=0;
    while(a[p]!='<'){
        ind.name[xi++]=a[p++];
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
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\t press : \n");
    printf("1. GLOBAL STATUS\n2. INDIA'S STATUS\n3. SYMPTOMS\n4. PRECAUTIONS\n5. QUIT\n");
    scanf("%d",&menu);
    printf("--------------------------------------------------------------------------------\n");
    return menu;
}
int print_menu_off(){
    int menu;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\t press : \n");
    printf("1. SYMPTOMS\n2. PRECAUTIONS\n3. RETRY \n4. QUIT\n");
    scanf("%d",&menu);
    printf("--------------------------------------------------------------------------------\n");
    return menu;
}
void print_sym(){
    printf("\n\n \t SYMPTOMS : \n\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("  People may be sick with the virus for 1 to 14 days before developing symptoms. The most common symptoms of coronavirus disease (COVID-19) are fever, tiredness, and dry cough. Most people (about 80%%) recover from the disease without needing special treatment.\n");
    printf("  More rarely, the disease can be serious and even fatal. Older people, and people with other medical conditions (such as asthma, diabetes, or heart disease), may be more vulnerable to becoming severely ill.\n");
    printf("  People may experince:\n");
    printf("    1. Cough\n");
    printf("    2. Fever\n");
    printf("    3. Tiredness\n");
    printf("    4. Difficulty in breathing (severe cases)\n\n");
    printf("--------------------------------------------------------------------------------\n");
}
void print_info(){
    printf("\n\n\t PRECAUTIONS : \n\n");
    printf("--------------------------------------------------------------------------------\n");
    printf("1. Wash your hands properly: \n");
    printf("\t Washing your hands with soap and water or using alcohol based hand rub kills viruses that may be on your hands.\n");
    printf("2. Maintain social distancing (atleast 1m ie 3 ft):\n");
    printf("\t When someone coughs or sneezes they spray droplets from their nose or mouth which may contain virus. If you're to close, you can breathe in the droplets, including the COVID-19 virus if the coughing person has the disease.\n");
    printf("3. Avoid touching eyes, nose and mouth:\n");
    printf("\t Hands touch many surfaces and can pickup viruses. Once contaminated, hands can transfer the virus to the eyes, nose your mouth. From there, the virus can enter your body and can make you sick.\n");
    printf("4. Practice respiratory hygiene:\n");
    printf("\t Droplets spread virus. By following good respiratory hygiene like covering your mouth and nose while sneezing and coughing you protect the people around you from viruses like cold, flu, COVID-19.\n");
    printf("5. If you have fever, cough and difficulty breatthing, seek medical care early:\n");
    printf("\t National and local authorities will have the most up to date information on the situtation in  your area. Calling in advance will allow your health care provider to quickly direct you to the right health facility. this will also protect you and help prevent the spread of this viruses and other infections.\n");
    printf("6. Stay informed and follow advice given by your healthcare provider:\n");
    printf("\t National and local authorities will have up to date information on whether COVID-19 is spreading in your area. They are the best placed to advise on what people in your area should be doing to protect themselves.\n\n");
    printf("--------------------------------------------------------------------------------\n");
}

int main(){
    //file download 
    
    CURL *curl;
    FILE *fp;
    int result;
    retry:
    fp=fopen("data.html","wb");
    curl=curl_easy_init();
    curl_easy_setopt(curl,CURLOPT_URL,"https://www.worldometers.info/coronavirus/");
    curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
    curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
    result=curl_easy_perform(curl);
    printf("\n\nWELCOME TO TRACK-KARONA\n");
    if(result==CURLE_OK){
        printf("\n");
        int option=0;
        while(option!=5){
            option = print_menu();
	        if(option==1)
		        top10();
            else if(option==2)
		        ind_data();
            else if(option==3)
		        print_sym();
            else if(option==4)
                print_info();
            else
                break;
    }
    }
    else{
        printf("error %s \n Check your internet connection\n\n\tOFFLINE MODE \n",curl_easy_strerror(result));
        int option=0;
        while(option!=4){
            option = print_menu_off();
	        if(option==1)
		        print_sym();
            else if(option==2)
		        print_info();
            else if (option==3)
                goto retry;   
            else
                break;
    }
    }
    fclose(fp);
    curl_easy_cleanup(curl);
    //file download complete
    printf("--------------------------------------------------------------------------------\n");
    printf("THANK YOU\n");
    printf("--------------------------------------------------------------------------------\n");
    remove("data.html"); //to delete the file
    return 0;
}
