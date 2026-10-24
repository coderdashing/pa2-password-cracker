#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
int string_cap_match(char *s1, char *s2)
{
        // Your code here
    int i = 0;
    int oneChance = 0;
    while(s1[i] != 0 || s2[i] != 0){
        if(s2[i] == 0){
            return 0;
        }
        if(s1[i] == 0){
            return 0;
        }
        if(s1[i] != s2[i]){
           if(oneChance == 1){
               return 0;
           }
        
            if(s1[i] >= 'a' && s1[i] <= 'z'){
                if(s2[i] < 'A' || s2[i] > 'Z'){
                    return 0;
                }
                oneChance = 1;
            }
            else if(s2[i] >= 'a' && s2[i] <= 'z'){
                if(s1[i] < 'A' || s1[i] > 'Z'){
                    return 0;
                }
                oneChance = 1;
            }
            else{
                return 0;
            }
        }
        i++;
        
    }
        return 1; // placeholder
}

int main(int argc, char* argv[])
{
        // TODO: Read lines from stdin in a loop
        // Each line contains two strings separated by a space
        // Parse the two strings from each line
        // Call string_cap_match and print "match" or "miss"
        char buffer[201];
    char r1[100];
    char r2[100];
    int i1;
    int i2;
    int mainind;
    int ind2;
	char first_string[100];
	first_string[0] = '\0';
	char hex_hash[65];
	unsigned char hash[32];
	char final_hash[65];
	final_hash[65] = '\0';
	int size;
	char *scan1;
    while (1)
    {
        mainind = 0;
        scan1 = fgets(buffer,sizeof(buffer),stdin);
        if(scan1 == NULL){
            break;
        }
	
		size = (int)strlen(scan1);
		if(scan1[size-1] == '\n'){
			size--;
			scan1[size] = '\0';
		}
		SHA256(scan1,size,hash);
		for (int i = 0; i < 32; i++)
		{
			sprintf(&hex_hash[i * 2], "%02x", hash[i]);
		}
		hex_hash[65] = '\0';
		if(string_cap_match(hex_hash,argv[1])){
			for(int i = 0; i < size; i++){
				first_string[i] = scan1[i];
			}
			first_string[size] = '\0';
			for (int i = 0; i < 65; i++){
				final_hash[i] = hex_hash[i];
			}
			
		}
    	for (int i = 0; i < size; i++){
			if(scan1[i] >= 'a' && scan1[i] <= 'z'){
            	scan1[i] -= 32;
				SHA256(scan1,size,hash);
	        	for (int i = 0; i < 32; i++)
	       	 	{   
	            	sprintf(&hex_hash[i * 2], "%02x",hash[i]);
	        	}
 				hex_hash[65] = '\0';
 				if(string_cap_match(hex_hash,argv[1])){
	            	for(int i = 0; i < size; i++){
						first_string[i] = scan1[i];
					}
					first_string[size] = '\0';
					for(int i = 0; i < 65; i++){
						final_hash[i] = hex_hash[i];
					}
	        	}
				scan1[i] += 32;
			}
			else if (scan1[i] >= 'A' && scan1[i] <= 'Z'){
				scan1[i] += 32;
				SHA256(scan1,size,hash);
				for (int i = 0; i < 32; i++){
	            	sprintf(&hex_hash[i * 2], "%02x", hash[i]);
				}
				hex_hash[65] = '\0';
				if(string_cap_match(hex_hash,argv[1])){
					for (int i = 0; i < size; i++){
						first_string[i] = scan1[i];
					}
					first_string[size] = '\0';
					for(int i = 0; i < 65; i++){
						final_hash[i] = hex_hash[i];
					}
				}
				scan1[i] -= 32;
 	    	}
		
		}

	}
	if(first_string[0] == '\0'){
		printf("Did not find a matching password\n");
	}
	else{
		printf("Found password: SHA256(%s) = %s\n",first_string,final_hash);
	}
      return 0;
}
