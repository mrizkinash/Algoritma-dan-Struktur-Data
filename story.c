#include <stdio.h>
#include <stdlib.h>

#include <Windows.h>
#include <unistd.h>


void Narasi()
{
	printf("\n");
	printf("  ################################################################################\n");
	printf("  # Saat avatar Aang belum muncul, dunia menjadi kacau dan terjadi perang dunia. #\n");
	sleep(2);
	printf("  # Perang ini diikuti oleh 4 negara - ");
	sleep(2);
	printf("Api, ");
	sleep(1);
	printf("Air, ");
	sleep(1);
	printf("Tanah, ");
	sleep(1);
	printf("Udara.                   #\n");
	sleep(2);
	printf("  # Pada mulanya, keempat negara berada di keempat penjuru dunia.                #\n");
	sleep(2);
	printf("  # Mereka memiliki pasukan masing-masing dan jumlahnya terus bertambah.         #\n");
	sleep(2);
	printf("  # Siapakah yang akan memenangkan perang ini?                                   #\n");
	sleep(2);
	printf("  # Apakah dunia ini akan kembali tenang?                                        #\n");
	sleep(0.5);
	printf("  ################################################################################\n");
}

void MainTitle()
{
	sleep(2);
	printf("	           _              __          __        _     ___          __                        \n");
	printf("    /\\            | |             \\ \\        / /       | |   | \\ \\        / /               \n");
	printf("   /  \\__   ____ _| |_ __ _ _ __   \\ \\  /\\  / /__  _ __| | __| |\\ \\  /\\  / /_ _ _ __      \n");
	printf("  / /\\ \\ \\ / / _` | __/ _` | '__|   \\ \\/  \\/ / _ \\| '__| |/ _` | \\ \\/  \\/ / _` | '__|  \n");
	printf(" / ____ \\ V / (_| | || (_| | |       \\  /\\  / (_) | |  | | (_| |  \\  /\\  / (_| | |          \n");
	printf("/_/    \\_\\_/ \\__,_|\\__\\__,_|_|        \\/  \\/ \\___/|_|  |_|\\__,_|   \\/  \\/ \\__,_|_|   \n");
	sleep(1);
}

int main()
{
	Narasi();
	MainTitle();
	return 0;
}
