#include <utils.hpp>

/*--------------------------------------------------------------------------------
									Misc Utils Implementation
--------------------------------------------------------------------------------*/
vector<string> utils::read_lines(const string& filename) {

	ifstream file(filename);
	user_error(string("Invalid file: ") + filename, file.good());
	vector<string> lines;
	string curr;

	while (getline(file, curr))
	{
		if (curr.size() > 0)
			lines.push_back(curr);
	}
	file.close();
	return lines;
}

vector<string> utils::split(const string& s, char delimiter)
{
	vector<string> tokens;
	string token;
	istringstream token_stream(s);
	while (getline(token_stream, token, delimiter))
	{
		tokens.push_back(token);
	}
	return tokens;
}

vector<vector<bool>> utils::parse_lines(const& string filename)
{
	vector<vector<bool>> parsed_data;
	vector<string> raw_data = utils::read_lines(filename);
	vector<bool> temp;
	for(int i = 0; i < raw_data.size(); i++) //For each in the file:
	{
		raw_data[i] = utils::split(raw_data[i], ' '); //split it to a vector of 0's and 1's
		temp = convert_to_bool(raw_data[i]); //convert it to boolean
		parsed_data.push_back(temp); //Save it in the matrix
	}
	return parsed_data;
}

/*--------------------------------------------------------------------------------
								String Extentions
--------------------------------------------------------------------------------*/

string repeat(string str, const size_t n)
{
	if (n == 0) {
		str.clear();
		str.shrink_to_fit();
		return str;
	}
	else if (n == 1 || str.empty()) {
		return str;
	}
	const auto period = str.size();
	if (period == 1) {
		str.append(n - 1, str.front());
		return str;
	}
	str.reserve(period * n);
	size_t m{ 2 };
	for (; m < n; m *= 2) str += str;
	str.append(str.c_str(), (n - (m / 2)) * period);
	return str;
}

string operator*(string str, size_t n)
{
	return repeat(move(str), n);
}

//Our Extension:

vector<bool> convert_to_bool(vector<string> s)
{
	vector<bool> newbool;
	for(auto i = s.begin(); i != s.end(); i++)
	{
		if(i == "0")
		{
			newbool.push_down(false);
		}
		else
		{
			newbool.push_down(true);
		}
	}
	return newbool;
}