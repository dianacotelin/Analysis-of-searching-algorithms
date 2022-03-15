#include <stdio.h>
#include <string.h> 
#include <time.h>
#include <stdlib.h>
#define d 256
#define MAX 15
#define MAX2 30

int RK(char pat[], char txt[], int q) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; // valoare hash pentru pattern
    int t = 0; // valoare hash pentru txt 
    int h = 1; 
  
    // Valoarea lui h este pow(d, M-1)%q
    for (i = 0; i < M - 1; i++) 
        h = (h * d) % q; 
  
    // Se calculeaza valoarea hash a pattern-ului si al 
    // primului posibil pattern al textului
    for (i = 0; i < M; i++) { 
        p = (d * p + pat[i]) % q; 
        t = (d * t + txt[i]) % q; 
    } 
  
    // Se muta pattern-ul mai departe pozitie cu pozitie
    for (i = 0; i <= N - M; i++) { 
  
        // Se compara valorile hash ale pattern-ului si a secventei gasite 
        // daca sunt egale se verifica si caractere pentru a nu aparea 
        // conflicte
        if (p == t) { 
            
            for (j = 0; j < M; j++) { 
                if (txt[i + j] != pat[j]) 
                    break; 
            } 
  
            // Daca s-a gasit, se intoarce pozitia
            if (j == M) 
                return i;
        } 
  
        
        // Se calculeaza valoarea hash pentru urmatoarea fereastra
        if (i < N - M) { 
            t = (d * (t - txt[i] * h) + txt[i + M]) % q; 
  
            // Daca e negativa, o fac pozitiva 
            if (t < 0) 
                t = (t + q); 
        } 
    }

    return -1; 
}

int RK2(char *pat, char *txt, int q) 
{ 
    int M = strlen(pat); 
    int N = strlen(txt); 
    int i, j; 
    int p = 0; // valoare hash pentru pattern
    int t = 0; // valoare hash pentru txt 
    int h = 1; 
    int count = 0;
  
    // Valoarea lui h este pow(d, M-1)%q
    for (i = 0; i < M - 1; i++) 
        h = (h * d) % q; 
  
    // Se calculeaza valoarea hash a pattern-ului si al 
    // primului posibil pattern al textului
    for (i = 0; i < M; i++) { 
        p = (d * p + pat[i]) % q; 
        t = (d * t + txt[i]) % q; 
    } 
  
    // Se muta pattern-ul mai departe pozitie cu pozitie
    for (i = 0; i <= N - M; i++) { 
  
        // Se compara valorile hash ale pattern-ului si a secventei gasite 
        // daca sunt egale se verifica si caractere pentru a nu aparea 
        // conflicte
        if (p == t) { 
            
            for (j = 0; j < M; j++) { 
                if (txt[i + j] != pat[j]) 
                    break; 
            } 
  
            // Daca s-a gasit, se numara
            if (j == M) 
                count ++;
        } 
  
        
        // Se calculeaza valoarea hash pentru urmatoarea fereastra
        if (i < N - M) { 
            t = (d * (t - txt[i] * h) + txt[i + M]) % q; 
  
            // Daca e negativa, o fac pozitiva 
            if (t < 0) 
                t = (t + q); 
        } 
    }

    return count; 
}

int apply_RK(char *pat, char *txt, int q, FILE *out)
{

    int i, k, l, len, len1;
    len = strlen(pat);
    len1 = len;
    char found = '0';

    if ( RK(pat, txt, q) >= 0) {       //daca se gaseste tot sirul "pat" in    
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

            //se formeaza substringuri in ordine descrescatoare a lungimii
            k = len1 - 1;            
            l = 0;

            while (k < len) {
                int count = 0;
                for (i = l; i <= k; i++, count++) {
                    str[count] = pat[i];
                }

                str[count] = '\0';
                if (RK(str, txt, q) >= 0) { 
                    //se cauta substringul in txt cu RK
                    fputs(str, out);
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
    int q = 101;
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
    //fputs("--RK Solution--\n", out);
    t = clock();
    if(number == 1){
        found = apply_RK(pat, txt, q, out);
        if (!found) {
            fputs("Nu s-a gasit nicio secventa comuna!", out);
        }
    }
    else {
        number2 = RK2(pat, txt, q);
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
