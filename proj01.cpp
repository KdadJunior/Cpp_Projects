#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//////////////////////////// Your Code //////////////////////////

/////////////////////////////////////////////////////////////////

void load_dictionary(const std::string &filename,
                     std::vector<std::string> &positiveWords,
                     std::vector<std::string> &negativeWords);
void load_dataset(const std::string &filename, std::vector<std::string> &titles,
                  std::vector<int> &years, std::vector<double> &ratings,
                  std::vector<std::string> &reviews);

//////////////////////////// Your Code //////////////////////////

/////////////////////////////////////////////////////////////////

// The main function
int main() {
  // File paths
  const std::string dataset1_path{"set1.csv"};
  const std::string dataset2_path{"set2.csv"};
  const std::string dictionary_path{"dictionary.txt"};

  // Load the word dictionary
  std::vector<std::string> positiveWords, negativeWords;
  load_dictionary(dictionary_path, positiveWords, negativeWords);

  // Load the datasets
  std::vector<std::string> titles1, titles2;
  std::vector<int> years1, years2;
  std::vector<double> ratings1, ratings2;
  std::vector<std::string> reviews1, reviews2;

  load_dataset(dataset1_path, titles1, years1, ratings1, reviews1);
  load_dataset(dataset2_path, titles2, years2, ratings2, reviews2);

  //////////////////////////// Your Code //////////////////////////

  /////////////////////////////////////////////////////////////////

  return 0;
}

// Loads the dictionary.txt file into two vectors of positiveWords and
// negativeWords
void load_dictionary(const std::string &filename,
                     std::vector<std::string> &positiveWords,
                     std::vector<std::string> &negativeWords) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening dictionary file." << std::endl;
    return;
  }
  std::string line;
  std::getline(file, line);
  const char delimiter{','};
  std::string token;
  std::stringstream posStream(line);
  while (std::getline(posStream, token, delimiter)) {
    positiveWords.push_back(token);
  }
  std::getline(file, line);
  std::stringstream negStream(line);
  while (std::getline(negStream, token, delimiter)) {
    negativeWords.push_back(token);
  }
}

// Loads the dataset into tokens representing each column
void load_dataset(const std::string &filename, std::vector<std::string> &titles,
                  std::vector<int> &years, std::vector<double> &ratings,
                  std::vector<std::string> &reviews) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Error opening dataset file: " << filename << std::endl;
    return;
  }
  std::string line, title, review;
  int year;
  double rating;
  std::string temp;  // Skip the first line of the datasets (headers)
  getline(file, line);
  while (getline(file, line)) {
    std::stringstream ss(line);

    getline(ss, title, ',');
    getline(ss, temp, ',');
    year = std::stoi(temp);
    getline(ss, temp, ',');
    rating = std::stod(temp);
    getline(ss, review);
    titles.push_back(title);
    years.push_back(year);
    ratings.push_back(rating);
    reviews.push_back(review);
  }
  file.close();
}

//////////////////////////// Your Code //////////////////////////

/////////////////////////////////////////////////////////////////