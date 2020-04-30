#include <stdio.h>
#include <string.h>
#include <jansson.h>
#include<curl/curl.h>

struct data_all_country{
	char country_name[100];
	int total_confirmed;
	int new_confirmed;
	int total_deaths;
	int new_deaths;
	int total_recovered;
	int new_recovered;
};
int print_menu(){
    int menu;
    printf("\n--------------------------------------------------------------------------------\n");
    printf("\t press : \n");
    printf("1. GLOBAL STATUS\n2. INDIA'S STATUS\n3. SYMPTOMS\n4. PRECAUTIONS\n5. QUIT\n");
    scanf("%d",&menu);
    printf("--------------------------------------------------------------------------------\n");
    return menu;
}

void india(struct data_all_country data_ind[])
{
	for(int i=0;i<243;i++)
	{
		if(strcmp(data_ind[i].country_name,"India")==0)
		{
			printf("--------------------------------------------------------------------------------\n");
			printf("%s \n",data_ind[i].country_name);
			printf("--------------------------------------------------------------------------------\n");
			printf("total cases --> %d \nnew cases --> +%d \ntotal deaths --> %d \nnew deaths --> +%d \ntotal recovered --> %d\nnew recoverd cases --> +%d\n",data_ind[i].total_confirmed,data_ind[i].new_confirmed,data_ind[i].total_deaths,data_ind[i].new_deaths,data_ind[i].total_recovered,data_ind[i].new_recovered);
			break;
		}
	}
}

void top_ten(struct data_all_country data_country[])
{
	char temp_name[100];
	int temp;
	for(int j=0;j<243;j++)
	{
		for(int i=0;i<242;i++)
		{
			if(data_country[i].total_confirmed < data_country[i+1].total_confirmed)
			{
				temp = data_country[i].total_confirmed;
				data_country[i].total_confirmed = data_country[i+1].total_confirmed;
				data_country[i+1].total_confirmed = temp;

				temp = data_country[i].new_confirmed;
				data_country[i].new_confirmed = data_country[i+1].new_confirmed;
				data_country[i+1].new_confirmed = temp;

				temp = data_country[i].total_deaths;
				data_country[i].total_deaths = data_country[i+1].total_deaths;
				data_country[i+1].total_deaths = temp;

				temp = data_country[i].new_deaths;
				data_country[i].new_deaths = data_country[i+1].new_deaths;
				data_country[i+1].new_deaths = temp;

				temp = data_country[i].total_recovered;
				data_country[i].total_recovered = data_country[i+1].total_recovered;
				data_country[i+1].total_recovered = temp;

				temp = data_country[i].new_recovered;
				data_country[i].new_recovered = data_country[i+1].new_recovered;
				data_country[i+1].new_recovered = temp;

				strcpy(temp_name,data_country[i].country_name);
				strcpy(data_country[i].country_name,data_country[i+1].country_name);
				strcpy(data_country[i+1].country_name,temp_name);
			}
		}
	}
	
	for(int i=0;i<10;i++)
	{
		printf("--------------------------------------------------------------------------------\n");
		printf("%d. %s \n",i+1,data_country[i].country_name);
		printf("--------------------------------------------------------------------------------\n");
		printf("total cases --> %d \nnew cases --> +%d \ntotal deaths --> %d \nnew deaths --> +%d \ntotal recovered --> %d\nnew recoverd cases --> +%d\n",data_country[i].total_confirmed,data_country[i].new_confirmed,data_country[i].total_deaths,data_country[i].new_deaths,data_country[i].total_recovered,data_country[i].new_recovered);
	}	
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


int main()
{
	CURL *curl;
	FILE *fp;
	int result;
	retry:
	fp=fopen("data.json","wb");
	curl=curl_easy_init();
	curl_easy_setopt(curl,CURLOPT_URL,"https://api.covid19api.com/summary");
	curl_easy_setopt(curl,CURLOPT_WRITEDATA,fp);
	curl_easy_setopt(curl,CURLOPT_FAILONERROR,1L);
	result=curl_easy_perform(curl);
	printf("\n\nWELCOME TO TRACK-KARONA\n");
	fclose(fp);
	curl_easy_cleanup(curl);


	size_t i;
	char *text;
	struct data_all_country data_country[250];
	json_t *root;
	json_error_t error;
	root = json_load_file("data.json",0,&error);
	json_t *data, *sha, *commit, *message, *country_array,*country,*country_name;
	json_t *total_confirmed,*new_confirmed, *total_deaths, *new_deaths, *total_recovered,*new_recovered;
	country_array = json_object_get(root,"Countries");
	for(int i=0;i< json_array_size(country_array);i++)
	{
		country = json_array_get(country_array,i);
		if(!json_is_object(country))
		{
		    fprintf(stderr, "error: commit data %d is not an object\n", (int)(i + 1));
		    json_decref(root);
		    return 1;
        	}
		country_name = json_object_get(country,"Country");
		total_confirmed = json_object_get(country,"TotalConfirmed");
		data_country[i].total_confirmed = json_integer_value(total_confirmed);
		new_confirmed = json_object_get(country,"NewConfirmed");
		data_country[i].new_confirmed = json_integer_value(new_confirmed);
		total_deaths = json_object_get(country,"TotalDeaths");
		data_country[i].total_deaths = json_integer_value(total_deaths);
		new_deaths = json_object_get(country,"NewDeaths");
		data_country[i].new_deaths = json_integer_value(new_deaths);
		total_recovered = json_object_get(country,"TotalRecovered");
		data_country[i].total_recovered = json_integer_value(total_recovered);
		new_recovered = json_object_get(country,"NewRecovered");
		data_country[i].new_recovered = json_integer_value(new_recovered);
		strcpy(data_country[i].country_name,json_string_value(country_name));
		 
	}
	printf("\n");
        int option=0;
        while(option!=5){
            option = print_menu();
	        if(option==1)
		        top_ten(data_country);
            else if(option==2)
		        india(data_country);
            else if(option==3)
		        print_sym();
            else if(option==4)
                print_info();
            else
                break;
	}
	remove("data.json"); //to delete the file
}
