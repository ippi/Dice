/*
 *  _______     ________    ________    ________    __
 * |   __  \   |__    __|  |   _____|  |   _____|  |  |
 * |  |  |  |     |  |     |  |        |  |_____   |  |
 * |  |  |  |     |  |     |  |        |   _____|  |__|
 * |  |__|  |   __|  |__   |  |_____   |  |_____    __
 * |_______/   |________|  |________|  |________|  |__|
 *
 * Dice! QQ Dice Robot for TRPG
 * Copyright (C) 2018-2019 w4123���
 *
 * This program is free software: you can redistribute it and/or modify it under the terms
 * of the GNU Affero General Public License as published by the Free Software Foundation,
 * either version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License along with this
 * program. If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#ifndef DICE_MSG_FORMAT
#define DICE_MSG_FORMAT
#include <string>
#include <map>
#include <vector>
using std::string;
std::string format(std::string str, const std::initializer_list<const std::string>& replace_str);
std::string format(std::string str, const std::map<std::string, std::string>& replace_str, std::map<std::string, std::string> str_tmp = {});

class ResList {
	std::vector<std::string> vRes;
	unsigned int intMaxLen = 0;
	string sDot = " ";
public:
	ResList() = default;
	ResList(std::string s, std::string dot) :sDot(dot) {
		vRes.push_back(s);
		intMaxLen = s.length();
	}
	ResList& operator<<(std::string s) {
		if (s.empty())return *this;
		vRes.push_back(s);
		if (s.length() > intMaxLen)intMaxLen = s.length();
		return *this;
	}
	std::string show() {
		std::string s;
		if (intMaxLen > 10) {
			for (auto it : vRes) {
				s += "\n" + it;
			}
		}
		else {
			for (auto it = vRes.begin(); it != vRes.end(); it++) {
				if (it == vRes.begin())s = *it;
				else s += sDot + *it;
			}
		}
		return s;
	}
	void setDot(string s) {
		sDot = s;
	}
};
#endif /*DICE_MSG_FORMAT*/
