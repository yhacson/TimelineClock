#include "TimeLineClock.h"

void main(void)
{
	TimeLineClock clock;
	clock.Init();
	clock.Start();

	int32 nFps;
	float32 fScale;
	cout << "设置fps：";
	cin >> nFps;
	cout << "设置速率：";
	cin >> fScale;
	clock.SetFPS(nFps);
	clock.SetScale(fScale);

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
				cout << "one second pass" << endl;
				count = 0;
			}
		}
	}
}