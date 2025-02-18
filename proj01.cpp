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

  // Check if dictionary is empty
  if (positiveWords.empty() && negativeWords.empty()) {
    std::cerr << "Error: Dictionary file is empty. Exiting program." << std::endl;
    return 1;
  }

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

  int posCount1 = 0, negCount1 = 0, incCount1 = 0;
  int posCount2 = 0, negCount2 = 0, incCount2 = 0;

  // Sentiment analysis for set 1
  for(const std::string& review : reviews1){
    std::string sentiment = determine_sentiment(review, positiveWords, negativeWords);
    if (sentiment == "positive"){
      posCount1++;
    }
    else if (sentiment == "negative"){
      negCount1++;
    }
    else{
      incCount1++;
    }
  }

  // Sentiment analysis for set 2
  for(const std::string& review : reviews2){
    std::string sentiment = determine_sentiment(review, positiveWords, negativeWords);
    if (sentiment == "positive"){
      posCount2++;
    }
    else if (sentiment == "negative"){
      negCount2++;
    }
    else{
      incCount2++;
    }
  }

  // Determine Overall Best Title(s)
  double highestRating = std::max(max1, max2);
  std::vector<std::string> bestMovies;
  
  for (size_t i = 0; i < ratings1.size(); ++i) {
      if (ratings1[i] == highestRating) {
          bestMovies.push_back(titles1[i]);
      }
  }
  for (size_t i = 0; i < ratings2.size(); ++i) {
      if (ratings2[i] == highestRating) {
          bestMovies.push_back(titles2[i]);
      }
  }

  // Determine Overall Worst Title(s)
  double lowestRating = std::min(min1, min2);
  std::vector<std::string> worstMovies;
  
  for (size_t i = 0; i < ratings1.size(); ++i) {
      if (ratings1[i] == lowestRating) {
          worstMovies.push_back(titles1[i]);
      }
  }
  for (size_t i = 0; i < ratings2.size(); ++i) {
      if (ratings2[i] == lowestRating) {
          worstMovies.push_back(titles2[i]);
      }
  }

    // Display the results
    std::cout << std::fixed << std::setprecision(2);
    std::cout << std::left;

    std::cout << std::setw(16) << "" << std::setw(16) << "Set 1" << std::setw(15) << "Set 2" << std::endl;
    std::cout << std::string(48, '-') << std::endl;  // Separator line

    std::cout << std::setw(16) << "Count:" << std::setw(16) << ratings1.size() << std::setw(15) << ratings2.size() << std::endl;
    std::cout << std::setw(16) << "Mean:" << std::setw(16) << mean1 << std::setw(15) << mean2 << std::endl;
    std::cout << std::setw(16) << "STDV:" << std::setw(16) << stddev1 << std::setw(15) << stddev2 << std::endl;
    std::cout << std::setw(16) << "Min:" << std::setw(16) << min1 << std::setw(15) << min2 << std::endl;
    std::cout << std::setw(16) << "Max:" << std::setw(16) << max1 << std::setw(15) << max2 << std::endl;
    std::cout << std::setw(16) << "Pos:" << std::setw(16) << posCount1 << std::setw(15) << posCount2 << std::endl;
    std::cout << std::setw(16) << "Neg:" << std::setw(16) << negCount1 << std::setw(15) << negCount2 << std::endl;
    std::cout << std::setw(16) << "Inc:" << std::setw(16) << incCount1 << std::setw(15) << incCount2 << std::endl;

    // Display Overall Best Titles (Handling Ties)
  std::cout << "Overall Best Title: ";
  for (size_t i = 0; i < bestMovies.size(); ++i) {
      if (i > 0) std::cout << ", ";
      std::cout << bestMovies[i];
  }
  std::cout << std::endl;

  // Display Overall Worst Titles (Handling Ties)
  std::cout << "Overall Worst Title: ";
  for (size_t i = 0; i < worstMovies.size(); ++i) {
      if (i > 0) std::cout << ", ";
      std::cout << worstMovies[i];
  }
  std::cout << std::endl;

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

    // Check if the line is malformed (missing fields)
    if (!std::getline(ss, title, ',') ||
        !std::getline(ss, temp, ',') ||
        !std::getline(ss, temp, ',') ||
        !std::getline(ss, review)) {
        std::cerr << "Warning: Malformed line in dataset. Skipping." << std::endl;
        continue;
    }

    // Handle invalid year or rating
    try {
        year = std::stoi(temp);
        rating = std::stod(temp);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Warning: Invalid year or rating. Skipping line." << std::endl;
        continue;
    }

    // Add valid data to vectors
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
    std::string lowerReview = review;
    std::transform(lowerReview.begin(), lowerReview.end(), lowerReview.begin(), ::tolower);
    for (const std::string& word : words) {
        std::string lowerWord = word;
        std::transform(lowerWord.begin(), lowerWord.end(), lowerWord.begin(), ::tolower);
        size_t pos = lowerReview.find(lowerWord);
        while (pos != std::string::npos) {
            count++;
            pos = lowerReview.find(lowerWord, pos + lowerWord.length());
        }
    }
    return count;
}

std::string determine_sentiment(const std::string& review, 
                              const std::vector<std::string>& positiveWords, 
                              const std::vector<std::string>& negativeWords) {
    int posCount = count_words(review, positiveWords);
    int negCount = count_words(review, negativeWords);

    if (posCount > negCount) {
      return "positive";
    } else if (negCount > posCount) {
      return "negative";
    } else {
      return "inconclusive";
    }
}

/////////////////////////////////////////////////////////////////