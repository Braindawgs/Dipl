// gpio mode 12 down -- Za pulldown pin10(ulaz)
var GPIO = require('onoff').Gpio,
	led = new GPIO(17, 'out'),
	button = new GPIO(10,'in', 'both','down');

process.stdout.write("Init Complete");

button.watch(function light(err, state)
{
if(1 == state)
	{
	led.writeSync(1);
	}
else
	{
	led.writeSync(0);	
	}
});

