#include<stdio.h>
#include<elf.h>

int main(int argc, char * argv[])
{
	long *p = (long *)argv;
	int i;
	Elf64_auxv_t *aux;

	printf("Argument count:%ld\n", *(p-1) );
	for(i=0; i<*(p-1); i++)
	{
		printf("Argument %d : %s\n", i, (char *)*(p+i) );
	}
	p += i;
	p++;

	printf("Environment:\n");
	while(*p)
	{
		printf("%s\n", (char *)*p);
		p++;
	}

	p++;

	printf("Auxiliary Vectors:\n");
	aux = (Elf64_auxv_t *)p;
	while(aux->a_type != AT_NULL)
	{
		printf("Type: %02d Value: %x\n", (int)aux->a_type, (unsigned int)aux->a_un.a_val);
		aux++;
	}

	return 0;
}
