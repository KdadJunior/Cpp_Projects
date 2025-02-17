#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

//////////////////////////// Your Code //////////////////////////

#include <cmath>
#include <iomanip>
#include <algorithm>
#include <numeric>

/////////////////////////////////////////////////////////////////

void load_dictionary(const std::string &filename,
                     std::vector<std::string> &positiveWords,
                     std::vector<std::string> &negativeWords);
void load_dataset(const std::string &filename, std::vector<std::string> &titles,
                  std::vector<int> &years, std::vector<double> &ratings,
                  std::vector<std::string> &reviews);

//////////////////////////// Your Code //////////////////////////

double calculate_mean(const std::vector<double>& ratings);
double calculate_standard_deviation(const std::vector<double>& ratings, double mean);
int count_words(const std::string& review, const std::vector<std::string>& words);
std::string determine_sentiment(const std::string& review, 
                              const std::vector<std::string>& positiveWords, 
                              const std::vector<std::string>& negativeWords);

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

  // Handle empty dataset case
  if (ratings1.empty() || ratings2.empty()) {
    std::cerr << "Error: One or both datasets are empty. Exiting program." << std::endl;
      return 1;
    }

  // Compute statistics for Set 1
  double mean1 = calculate_mean(ratings1);
  double stddev1 = calculate_standard_deviation(ratings1, mean1);
  double min1 = *std::min_element(ratings1.begin(), ratings1.end());
  double max1 = *std::max_element(ratings1.begin(), ratings1.end());

  // Compute statistics for Set 2
  double mean2 = calculate_mean(ratings2);
  double stddev2 = calculate_standard_deviation(ratings2, mean2);
  double min2 = *std::min_element(ratings2.begin(), ratings2.end());
  double max2 = *std::max_element(ratings2.begin(), ratings2.end());
------------------------------------------------------------------------------------------------------
  // Sentiment analysis
  int posCount1 = 0, negCount1 = 0, incCount1 = 0;
  for(const std::string& review : reviews1){
    std::string sentiment = determine_sentiment(review, positiveWords, negativeWords);
    if (sentiment == "positive") posCount++;
      else if (sentiment == "negative") negCount++;
      else incCount1++;
    }
  }
  --------------------------------------------------------------------------------------------------------
  determine_sentiment(reviews1, positiveWords, negativeWords);

  int posCount2 = 0, negCount2 = 0, incCount2 = 0;
  determine_sentiment(reviews2, positiveWords, negativeWords);

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
  std::string temp;
  std::getline(file, line); // Skip the first line of the datasets (headers)
  while (std::getline(file, line)) {
    std::stringstream ss(line);

    std::getline(ss, title, ',');
    std::getline(ss, temp, ',');
    year = std::stoi(temp);
    std::getline(ss, temp, ',');
    rating = std::stod(temp);
    std::getline(ss, review);
    titles.push_back(title);
    years.push_back(year);
    ratings.push_back(rating);
    reviews.push_back(review);
  }
  file.close();
}

//////////////////////////// Your Code //////////////////////////

double calculate_mean(const std::vector<double>& ratings) {
    double sum = 0.0;
    for (double rating : ratings){
      sum += rating;
    }
    return sum / ratings.size();
}

double calculate_standard_deviation(const std::vector<double>& ratings, double mean) {
    double variance = 0;
    for (double rating : ratings){
      variance += (rating - mean) * (rating - mean);
    }
    return sqrt(variance / ratings.size());
}

int count_words(const std::string& review, const std::vector<std::string>& words) {
    int count = 0;
    for (const std::string& word : words) {
        size_t pos = review.find(word);
        while (pos != std::string::npos) {
            count++;
            pos = review.find(word, pos + word.length());
        }
    }
    return count;
}

std::string determine_sentiment(const std::vector<std::string>& reviews, 
                              const std::vector<std::string>& positiveWords, 
                              const std::vector<std::string>& negativeWords) {
    std::string result = std::accumulate(reviews.begin() + 1, reviews.end(), reviews[0],
        [](const std::string& a, const std::string& b){
          return a + "," + b;
        });
    int posCount = count_words(result, positiveWords);
    int negCount = count_words(result, negativeWords);

    if (posCount > negCount) {
      return "positive";
    } else if (negCount > posCount) {
      return "negative";
    } else {
      return "inconclusive";
    }
}

/////////////////////////////////////////////////////////////////