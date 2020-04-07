//
#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define OK 0
#define INIT_ERR 1
#define REQ_ERR 2

#define URL "http://10.0.0.74:8000"

//GET
void curl_get(char* url, CURL *curl, CURLcode res) {
	long http_code = 0;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl could not execute --get: %s\n", curl_easy_strerror(res));
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("\nHTTP CODE: %ld\n", http_code);
		curl_easy_cleanup(curl);
	}
	//printf("Henlo, get: %s pls.\n", url);
}

//POST
void curl_post(char* url, char *curl_message, CURL *curl, CURLcode res) {
	long http_code = 0;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_POST, 1L);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
		curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(curl_message));
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl could not execute --post: %s\n", curl_easy_strerror(res));
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("\nHTTP CODE: %ld\n", http_code);
		curl_easy_cleanup(curl);
	}
}

//PUT
void curl_put(char* url, char *curl_message, CURL *curl, CURLcode res) {
	long http_code = 0;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl could not execute --put: %s\n", curl_easy_strerror(res));
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("\nHTTP CODE: %ld\n", http_code);
		curl_easy_cleanup(curl);
	}
}

//DELETE
void curl_delete(char* url, char *curl_message, CURL *curl, CURLcode res) {
	long http_code = 0;
	if(curl) {
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_message);
		res = curl_easy_perform(curl);
		if(res != CURLE_OK) {
			fprintf(stderr, "curl could not execute --delete: %s\n", curl_easy_strerror(res));
		}
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		printf("\nHTTP CODE: %ld\n", http_code);
		curl_easy_cleanup(curl);
	}
}

//HELP
void help_message() {
	printf("Help:\
	\n\t./hw --get --url\
	\n\t./hw --post --url <web_url> message\
	\n\t./hw --put --url <web_url> message\
	\n\t./hw --delete --url <web_url> message\
	\n\
	\n\t./hw -g -u <web_url>\
	\n\t./hw -o -u <web_url> message\
	\n\t./hw -p -u <web_url> message\
	\n\t./hw -d -u <web_url> message\
	\n\
	<web_url>:\
	\n\t http://localhost:port\
	\n\t or\
	\n\t http://www.website.com\n");
}

//Usage for program (ideal)
void usage_message() {
	printf("Usage:\
	\n\t./hw --get --url\
	\n\t./hw --post --url <web_url> message\
	\n\t./hw --put --url <web_url> message\
	\n\t./hw --delete --url <web_url> message\
	\n\t./hw --help\
	\n\
	\n\t./hw -g -u\
	\n\t./hw -o -u <web_url> message\
	\n\t./hw -p -u <web_url> message\
	\n\t./hw -d -u <web_url> message\
	\n\t./hw -h\
	\n\
	<web_url>:\
	\n\t http://localhost:port\
	\n\t or\
	\n\t http://www.website.com\n");
}

int string_check(char *message) {
	char *http_str = "http://";
	int return_value;
	if(strstr(message, http_str) == NULL) {
		printf("\nMissing \"http://\" \n\n");
		usage_message();
		return_value = 0;
		return return_value;
	}
	else {
		char *local_str = "localhost";
		if(strstr(message, local_str) == NULL) {
			return_value = 1;
			return return_value;
		}
		else {
			char *colon_char = "host:";
			if(strstr(message, colon_char) == NULL) {
				printf("\nPlease specify a port after localhost\n\n");
				usage_message();
				return_value = 0;
				return return_value;
			}
			else {
				return_value =1;
				return return_value;
			}
		}
	}

}

int main(int argc, char *argv[]) {
	//printf("argc: %d\n", argc);
	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	int i, j;
	//Starts at 1 because we know that ./hw will always be the first arg
	for(i=1; i < argc; i++) {
		//printf("Argument %d: %s\n", i, argv[i]);
		if((strcmp(argv[i], "--get") == 0) || (strcmp(argv[i], "-g") == 0)) {
			//printf("You called --get\n");
			for(j=1; j < argc; j++) {
				if(i == j) {
					;
				}
				if((strcmp(argv[j], "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
					if(string_check(argv[j+1])) {
						curl_get(argv[j+1], curl, res);
					}
				return OK;
				}
			}
		}
		else if((strcmp(argv[i], "--post") == 0) || (strcmp(argv[i], "-o") == 0)) {
			printf("You called --post\n");
			for(j=0; j < argc; j++) {
				if(i == j) {
					;
				}
				if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
					int k;
					int message_len = 0;
					for(k=4; k < argc; k++) {
						message_len += strlen(argv[k]) + 1;
					}
					//printf("Message Length is %d\n", message_len);
					char curl_message[message_len];
					for(k=4; k < argc; k++) {
						strcat(curl_message, argv[k]);
						if((k + 1) == argc) {
							;
						}
						else {
							strcat(curl_message, " ");
						}
					}
					//printf("String: %s\n", curl_message);
					if(string_check(argv[j+1])) {
						curl_post(argv[j+1], curl_message, curl, res);
					}
					return OK;
				}
			}
		}
		else if((strcmp(argv[i], "--put") == 0) || (strcmp(argv[i], "-p") == 0)) {
			//printf("You called --put\n");
			for(j=0; j < argc; j++) {
				if(i == j) {
					;
				}
				if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
					int k;
					int message_len = 0;
					for(k=4; k < argc; k++) {
						message_len += strlen(argv[k]) + 1;
					}
					//printf("Message Length is %d\n", message_len);
					char curl_message[message_len];
					for(k=4; k < argc; k++) {
						strcat(curl_message, argv[k]);
						if((k + 1) == argc) {
							;
						}
						else {
							strcat(curl_message, " ");
						}
					}
					if(string_check(argv[j+1])) {
						curl_put(argv[j+1], curl_message, curl, res);
					}
					return OK;

				} 
			}
		}
		else if((strcmp(argv[i], "--delete") == 0) || (strcmp(argv[i], "-d") == 0)) {
			//printf("You called --delete\n");
			for(j=0; j < argc; j++) {
				if(i == j) {
					;
				}
				if((strcmp(argv[j],  "--url") == 0) || (strcmp(argv[j], "-u") == 0)) {
					int k;
					int message_len = 0;
					for(k=4; k < argc; k++) {
						message_len += strlen(argv[k]) + 1;
					}
					//printf("Message Length is %d\n", message_len);
					char curl_message[message_len];
					for(k=4; k < argc; k++) {
						strcat(curl_message, argv[k]);
						if((k + 1) == argc) {
							;
						}
						else {
							strcat(curl_message, " ");
						}
					}
					if(string_check(argv[j+1])) {
						curl_delete(argv[j+1], curl_message, curl, res);
					}
					return OK;

				} 
			}
		}
		else if((strcmp(argv[i], "--help") == 0) || (strcmp(argv[i], "-h") == 0)) {
			help_message();
			return OK;
		} 
	}
	usage_message();
	return OK;
}

/*
std::cout << "This is my print message!\n";
*/
