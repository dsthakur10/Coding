
/*

Implement atoi function.

NOTE : Input may contain any random string like "123avsd", "-123", "lsdkfl", "123-125"

You have to return input value if the input is valid input string else return -1

Example 1:
Input: str = 123
Output: 123

Example 2:
Input: str = 21a
Output: -1
Explanation: Output is -1 as all characters are not digit only.

Example 3:
Input: str = -12
Output: -12
Explanation: Output is -12 as it is a valid integer.

*/


int atoi(string str) {

    // flag indicates whether given valid number is positive or negative
    bool flag = true;
    int value = 0;
    for(int i=0; i<str.size(); i++)
    {
        // allow '-' only in the 1st place
        if(i == 0 && str[i] == '-')
        {
            flag = false;
            continue;
        }

        int ch = str[i] - '0';

        if(ch > 9 || ch < 0)
            return -1;

        value = value * 10 + ch;
    }

    if(flag)
        return value;

    else
        return -value;
}

