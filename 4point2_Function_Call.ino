/*
Leigh Rowell, ID: 219309149
SIT210 Embedded Systems Development
Ontrack Task 4.2HD
Calling a function from the web to device

ref:
https://docs.particle.io/reference/device-os/firmware/photon/#cloud-functions
*/

/*
Task Objective
This task will introduce you to the concept of remotely calling a function from the web to run on your Particle device.
Scenario/requirements: A remote junction in rural Australia is in need of a traffic light. Given remote nature of the area
and lack of facilities to implement an automated traffic junction, we are asked by the authorities to design a system that
allows them to control the traffic light remotely. We will be using a particle device, and three LEDs to demonstrate a
working prototype.

SIT210: Embedded Systems Development
Steps:
1. Complete a simple circuit board using Particle device that includes: 3 LEDs connected to 3 pins on the device that
allows you to turn them on and off separately. Label the 3 LEDs with “red”, “green”, and “blue”.
 a. Optionally if you have them, use 3 LED with 3 different colours (red, green, blue)
 b. Alternatively, you might want to use an RGB LED.
2. Write a function on the particle device that takes in a string argument, “red”, “green” or “blue” to toggle the corresponding LED on/off.
3. Expose your method to the cloud using Particle.function() call (you need to research particle docs to see how you can achieve this, including apis and tocken IDs).
4. Create a simple HTML page that has 3 checkbox/buttons form to use to toggle your LEDs on your device.
5. Open the HTML file and use the checkbox to turn toggle the LEDs on your photon.
*/

// The following HTML code will call this function and operate the LEDs from within a web browser..

/*
<!
Leigh Rowell
ID: 219309149
SIT210
Ontrack Task 4.2HD
-->

<!DOCTYPE html>
<html>
  <script src="http://ajax.googleapis.com/ajax/libs/jquery/1.3.2/jquery.min.js" type="text/javascript" charset="utf-8"></script>
<body>
    <h1 style="text-align:center";>Leigh Rowell - SIT210 - Ontrack 4.2HD</h1>
    <h3 style="text-align:center";>Click the buttons below to change the status of the LED light</h3>
    
    <div style="text-align:center";>
        <br><br> 
            <button type = "button" id="fbtn" onclick="setDir('red')" > Red LED </button>
        <br><br>
            <button type = "button" id="fbtn" onclick="setDir('blue')" > Blue LED </button>
        <br><br>
            <button type = "button" id="fbtn" onclick="setDir('green')" > Green LED </button>
        <br><br>
    </div>

    <script type="text/javascript">
        <! Replace the following variables with your unique device ID, and access token.. >
        var deviceID    = " YOUR ID HERE ";
        var accessToken = " YOUR ACCESS TOKEN HERE ";
        var func = "led_function";

        function setDir(value)
        {
        var requestURL = "https://api.particle.io/v1/devices/" +deviceID + "/" + func + "/";
        $.post( requestURL, { params: value, access_token: accessToken });
        }
    </script>

</body>
</html>
     
*/

// Define Pins
#define REDLED D4
#define BLUELED D5
#define GREENLED D6

// Bool variables for LED status.. true = on, false = off.
bool redLED = false;
bool blueLED = false;
bool greenLED = false;


void setup()
{
    // Declare pin modes
    pinMode(REDLED, OUTPUT);
    pinMode(BLUELED, OUTPUT);
    pinMode(GREENLED, OUTPUT);
    
    // Declare particle functions...
    // Particle.function(<cloud funtion name>, <device function to call>)   < I THINK!!!!
    Particle.function("led_function", led_function);
    //Particle.function("blue", blue_LED);
    //Particle.function("green", green_LED);
    
    // Start Serial Comms
    Serial.begin(9600);
    while (!Serial.available() && millis() < 30000) {
    Serial.println("Press any key to start.");
    Particle.process();
    delay(1000);
    }
    Serial.println("Ontrack Task 4.2HD");
    Serial.println("##################");
    
    
}

void loop()
{
    // Nothing to do here..
}


void change_LED(int LED, bool &boolVar)
{
    // Funtion takes an input for the LED light and corresponding bool variable, and will swap the LED on/off.
    Serial.println("LED Light change function called.");
    Serial.print("LED value: ");
    Serial.print(LED);
    Serial.print(". boolVar value: ");
    Serial.println(boolVar);
    if (boolVar)
    {
        // LED is on, turn it off.
        Serial.println("Turning LED off.");
        digitalWrite(LED, LOW);
        boolVar = false;
    }
    else
    {
        // Red LED is on, turn it on.
        Serial.println("Turning LED on.");
        digitalWrite(LED, HIGH);
        boolVar = true;
    }
}


int led_function(String args)
{
    // Function takes string argument and determines which LED to change...
    Serial.print("LED function called, args: ");
    Serial.println(args);
    
    int arg_int = -1;
    
    if (args == "red") arg_int = 0;
    if (args == "blue") arg_int = 1;
    if (args == "green") arg_int = 2;
    
    switch (arg_int)
    {
        case 0:
        {
            Serial.println("Red LED being passed...");
            change_LED(REDLED, redLED);
            break;
        }
        case 1:
        {
            Serial.println("Blue LED being passed...");
            change_LED(BLUELED, blueLED);
            break;
        }
        case 2:
        {
            Serial.println("Green LED being passed...");
            change_LED(GREENLED, greenLED);
            break;
        }
        default:
        {
            // Invalid argument passed...
            Serial.println("Not a valid argument. Doing nothing.");
        }
        
    }
}






