#include<stdio.h>
#include<curl/curl.h>
int main(int url, char **image){
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
        printf("download successful \n");
    }
    else{
        printf("error %s \n",curl_easy_strerror(result));
    }
    fclose(fp);
    curl_easy_cleanup(curl);
    return 0;
}