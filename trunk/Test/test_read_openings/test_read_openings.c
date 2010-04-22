/*test read_from_file read_database
 *
 * putza frectie sugere
 */
#include<stdio.h>
#include "../../read_from_file/read_from_file.h"
#include "../../Init/init.h"

int main()
{
	Init(INIT_ALL);

	FILE *g=fopen("output.txt","w");
	printf("mare scurgere\n");
	Read_openings();
	printf("\nmare scurgere\n");
	fclose(g);
	return 1;
}
