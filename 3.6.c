#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void jelkezelo(){
	printf("gecisszar\nSS");
}


int main()
{
while(1){
sleep(1);
	if(signal(SIGINT, jelkezelo)==SIG_IGN)
       signal(SIGINT, SIG_IGN);

}


}
