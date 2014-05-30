#include "TimeLineClock.h"

void main(void)
{
	TimeLineClock clock;
	clock.Init();
	clock.Start();
	clock.SetFPS(60);
	clock.SetScale(1);

	int32 count = 0;
	float64 dt;
	while(true)
	{
		dt = clock.Step();
		if(dt >= clock.GetInterval())
		{
			cout << count << " step:" << dt << endl;

			count++;
			if(count >= clock.GetFPS())
			{
				cout << "one second" << endl;
				count = 0;
			}
		}
	}
}