//
//  Utils.h
//  HearingView
//
//  Created by Imanolgo on 6/28/12.
//


#ifndef __UTILS_H__
#define __UTILS_H__

#include<string>
#include<vector>
#include<sstream>

std::string int2Str(int value)
{
    std::string s;
    std::stringstream out;
    out << value;
    s = out.str();
}


//std::vector<std::string> split(const std::string& s, char c) 
//{
//	std::vector<std::string> v;
//	int i = 0;
//    size_t found;
//    
//    found = s.find(c);
//    if (found==string::npos)
//    {
//		v.push_back(s);
//		return v;
//	}
//    
//	
//	while (found!=string::npos) {
//        int j = int(found);
//		v.push_back(s.substr(i, j));
//		i = ++j;
//        found = s.find(c,j);
//		if (found == string::npos )
//		{
//			v.push_back(s.substr(i, s.length()));
//		}
//	}
//    
//	return v;
//}


//std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
//    std::stringstream ss(s);
//    std::string item;
//    while(std::getline(ss, item, delim)) {
//        elems.push_back(item);
//    }
//    return elems;
//}
//
//
//std::vector<std::string> split(const std::string &s, char delim) {
//    std::vector<std::string> elems;
//    return split(s, delim, elems);
//}

#endif