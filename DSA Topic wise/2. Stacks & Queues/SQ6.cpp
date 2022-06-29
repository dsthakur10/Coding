/*

Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

    The path starts with a single slash '/'.
    Any two directories are separated by a single slash '/'.
    The path does not end with a trailing '/'.
    The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
    Return the simplified canonical path.

*/

#include <sstream>
#include<iostream>
#include<stack>
#include<string>
#include<algorithm>
#include<vector>

std::string simplifyPath(std::string path);
std::string simplifyPath2(std::string path);


int main()
{
    std::string path;

    std::cout << "Enter path:\n";
    std::cin >> path;

    std::cout << path.size() << "\n";

    path = simplifyPath2(path);

    std::cout << "\nSimplified Path name = "<< path;

    return 0;
}



std::string simplifyPath(std::string path)
{
    std::stack<std::string> st;
    std::string str;

    st.push("/");

    int i=1;
    int len = path.size();
    while(i<len)
    {
        str.clear();
        while(i < len && path[i] == '/')
        {
            if(st.top() != "/")
                st.push("/");
            i++;
        }

        while(i < len && path[i] != '/')
        {
            str += path[i];
            i++;
        }

        if(str == ".")
        {
            continue;
        }

        else if(str == "..")
        {
            if(st.size() != 1)
            {
                st.pop();                   // for /
                st.pop();                   // for directory
                //st.top();
            }
        }

        else
        {
            if(str.size() != 0)
                st.push(str);
        }
    }

    std::string temp;
    std::cout << "\nTOP = " << st.top();
    std::cout << "\nSize = "<< st.size();
/*
    if(st.size() == 1);
    {
        return "/";
    }
*/

    if(st.size() != 1 && st.top() == "/")               // deleting topmost '/' if it is not the only '/' on stack
        st.pop();

    std::cout << "\nTOP = " << st.top();
    std::cout << "\nSize = "<< st.size();

    while(!st.empty())
    {
        temp.insert(0,st.top());
        st.pop();
    }

    return temp;
}



// ------------------------- Method-2 ------------------------------


std::string simplifyPath2(std::string path)
{
    std::string temp;
    std::vector<std::string> stk;
    std::stringstream ss(path);             // stringstream associates a string object with a stream allowing you to read from string as if it were a stream (std::cin)

    while(getline(ss,temp,'/'))             // getline() is a std library function that is used to read a string or a line from an input stream.
                                            // It extracts characters from the input stream and appends it to the string object until the delimiting character is encountered.
                                            // While doing so the previously stored value in the string object str will be replaced by the input string if any
    {
        if (temp == "" or temp == ".")
            continue;
        if (temp == ".." and !stk.empty())
            stk.pop_back();
        else if (temp != "..")
            stk.push_back(temp);
    }

    temp.clear();
    for(auto str : stk)                     // rotating through vector of strings that contain directoy names in order
        temp += "/" + str;

    return temp.empty() ? "/" : temp;

}
