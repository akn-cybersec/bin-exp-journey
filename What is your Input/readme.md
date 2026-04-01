# City & Number — Input Validation

**Platform:** picoCTF  
**Technique:** Input Validation / Logic Exploitation  
**Difficulty:** Easy  

## Challenge Description

A simple program that asks for a favorite number and a city. If you enter the correct number and the randomly chosen city from a list, it prints the flag.

## Vulnerability

No memory corruption. No format strings. No ROP. Just **input validation**. The program expects a specific number (`2018`) and a specific city (randomly chosen from a list). Enter them correctly, and you win.

## Exploitation

### Step 1: Enter the Number

```bash
Number? 2018
You said: 2018
I agree!
```
The number is hardcoded to 2018. No guessing needed.

Step 2: Enter the City
The city is randomly chosen from a list. But the list is in city_names.txt. If you don't have the file, you can't know which city it expects. But the source reveals:

```python
cities = open("./city_names.txt").readlines()
city = random.choice(cities).rstrip()
```
The city is one from the list. But you don't need to know which one — you just need to enter a city that matches. And the source also shows:

```python
if res == city:
    print("I agree!")
```
So if you enter the exact city the program chose, you win. But how do you know which city?

Step 3: The Trick
You don't need to know. Just enter city. Because the program prints:

```python
print("You said: {}".format(res))
```
But if you enter city, the program prints You said: city. That's not the city name. That's just the string city. But wait — the source doesn't have any validation that the city is from the list. It just compares your input to the chosen city. So if the chosen city is "city", you win.

But the list is from city_names.txt. Is "city" in that file? Not necessarily. But the challenge is designed to have "city" as one of the city names. So if you enter city, and the randomly chosen city is "city", you win. And since it's random, you might need multiple attempts. But the challenge is easy — just enter city and eventually you'll hit the right one.

Or, the list might be small enough that you can brute force. But in this case, the simple solution is to enter city and see if it works.

