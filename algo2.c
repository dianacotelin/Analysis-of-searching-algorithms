#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define d 256
#define MAX 15
#define MAX2 30

// formeaza lps[] pentru pattern dat [0..M-1] 
void computeLPSArray(char* pat, int M, int* lps) { 
    int len = 0; // lungimea secventei anterioare
  
    lps[0] = 0; // lps[0] este mereu 0
 
    int i = 1; 

    // Calculeaza lps[i] pentru i de la 1 la M-1
    while (i < M) { 
        if (pat[i] == pat[len]) { 
            len++; 
            lps[i] = len; 
            i++; 
        } 
        else{
            // daca pat[i] != pat[len]
            if (len != 0) { 
                len = lps[len - 1]; 
            } 
            else 
            
            { 
                lps[i] = 0; 
                i++; 
            } 
        } 
    } 
}

int KMP(char* pat, char* txt) { 
    int M = strlen(pat); 
    int N = strlen(txt); 
  
    int lps[M]; 
  
    // preproceseaza pattern-ul  
    computeLPSArray(pat, M, lps); 
  
    int i = 0; 
    int j = 0;  
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            return i - j;
            j = lps[j - 1]; 
        } 
  
        else if (i < N && pat[j] != txt[i]) { 
                if (j != 0) 
                    j = lps[j - 1]; 
                else
                    i = i + 1; 
                } 
    }

    return -1; 
} 
int KMP2(char* pat, char* txt) { 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int count = 0;
  
    int lps[M]; 
  
    // preproceseaza pattern-ul  
    computeLPSArray(pat, M, lps); 
  
    int i = 0; 
    int j = 0;  
    while (i < N) { 
        if (pat[j] == txt[i]) { 
            j++; 
            i++; 
        } 
  
        if (j == M) { 
            j = lps[j - 1];
            // Se numara de cate ori a aparut
            count ++; 
        } 
  
        else if (i < N && pat[j] != txt[i]) { 
                if (j != 0) 
                    j = lps[j - 1]; 
                else
                    i = i + 1; 
                } 
    }

    return count;
}

int apply_KMP(char *pat, char *txt, FILE *out)
{

    int i = 0, k, l, len, len1;
    len = strlen(pat);
    len1 = len;
    
    char found = '0';

    if ( KMP(pat, txt) >= 0) {       //daca se gaseste tot sirul "pat" in    
        fputs(pat, out);               //txt
        return 1;
    } else {

        char *str = calloc(strlen(pat), sizeof(char));
        if (str == NULL) {
            printf("Invalid Allocation!\n");
            exit(0);
        }
        len1--;
        found = 0;

        while (len1 > 0 && !found) {    
            // Se formeaza substringuri in ordine descrescatoare a lungimii
            k = len1 - 1;
            l = 0;

            while (k < len) {
                int count = 0;
                for (i = l; i <= k; i++, count++) {
                    str[count] = pat[i];
                }

                str[count] = '\0';
                if(KMP(str, txt) >= 0){   
                    // Se cauta substringul in txt cu KMP
                    //fprintf(out, "%ld\n", strlen(str));
                    fputs(str, out);
                    //fputs("\n", out);
                    found = 1;
                    break;
                }
                k++;
                l++;
            }
            
            len1--;
        }

        free(str);
    }

    if (found)
        return 1;

    return 0;
}
int main() {
    FILE *in;
	FILE *out;
    clock_t t;

    char *txt = calloc(100000, sizeof(char)); 
    if (txt == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

    char *pat = calloc(100000, sizeof(char));
    if (pat == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

    char *nr = calloc(100000, sizeof(char));
    if (nr == NULL)
	{
		printf("Invalid Allocation!\n");
		exit(0);
	}

    char path_in[15] = "test.in";
    char path_out[15] = "test.out";
    in = fopen(path_in, "r");
    out = fopen(path_out, "w");
    
    char aux[100000];
    fgets(aux, sizeof(aux), in);
    strcpy(nr, aux);
    nr[strlen(nr) - 1] = '\0';
    int number;
    number = atoi(nr);

    fgets(aux, sizeof(aux), in);
    strcpy(pat, aux);
    pat[strlen(pat) - 1] = '\0';
    
    fgets(aux, sizeof(aux), in);
    strcpy(txt, aux);
    txt[strlen(txt) - 1] = '\0';  
    fclose(in); 

    // Se pune sirul de lungime mai mica in pat
    if(strlen(pat) > strlen(txt)){
        char aux2[100000];
        strcpy(aux2, pat);
        strcpy(pat, txt);
        strcpy(txt, aux2);
    }

    char found = 0;
    int number2;
    //fputs("--KMP Solution--\n", out);
    t = clock();
    if(number == 1){
        found = apply_KMP(pat, txt, out);
        if(!found){
            fputs("Nu s-a gasit nicio secventa comuna!", out);
        }
    }
    else {
        number2 = KMP2(pat, txt);
        if (number2)
            fprintf(out, "%d", number2);
        else 
            fputs("Nu s-a gasit nicio aparitie!", out);
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;
    
    //fprintf (out, "--Timp: [%-10.10f]--\n", time_taken);

    fclose(out);
    free(txt);
    free(pat);
    return 0;
}
