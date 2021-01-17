#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>

int main (int argc, char **argv)
{
  int n_count = 0; // event name count
  int w_count = 0; // event weight count
  int me_count = 0; // measure event count
  int max_me_count = 0; // number of lines in second file
  int line_count = 1; // number of lines in third file

  double threshold = 0;
  double event_weight_d = 0; // store converted event weight string
  double measure_event_d = 0; // store converted measure event string
  double measure_event_stdev = 0; // store standard deviation of event
  double distance = 0; // store distance calculated from third file
  double event_weight_array[20]; // array of event weights
  double measure_event_array[20]; // array of measure event from second file
  double event_average[20]; // array of event average of measured events
  double event_stdev[20]; // array of event standard deviation of measured events

  // initialisation of strings used to store measured events
  std::string measure_event1 = " ";
  std::string measure_event2 = " ";
  std::string measure_event3 = " ";
  std::string measure_event4 = " ";
  std::string measure_event5 = " ";
  std::string event_weight = " ";
  std::string event_name = " ";
  std::string name_array[20]; // array for storing event names

  std::ifstream input_file;

  if (argc > 4) // if more than four arguments send error, exit program
  {
    std::cerr << "Too many arguments, must have 4 arguments in total.\nExiting program..." << std::endl;
    return -1;
  }
  else if (argc < 4) // else if less than four arguments send error, exit program
  {
    std::cerr << "Need more arguments, must have 4 arguments in total.\nExiting program..." << std::endl;
    return -1;
  }

  input_file.open(argv[1]); // open first file

  if (!input_file) // if file not found send error, exit program
  {
    std::cerr << "No file found. Exiting program..." << std::endl;
    return -1;
  }
  else // else file found
  {
    std::cout << "File found..." << std::endl;
  }

  for (int i = 0; i < 20; i++) // initialisation of all arrays
  {
    event_weight_array[i] = 0;
    measure_event_array[i] = 0;
    event_average[i] = 0;
    event_stdev[i] = 0;
    name_array[i] = " ";
  }

  while (std::getline(input_file, event_name, ':')
  && std::getline(input_file, event_weight, ':'))
  {
    event_weight_d = std::stod(event_weight); // convert event weight string to double
    name_array[n_count] = event_name; // store event name in array
    event_weight_array[w_count] = event_weight_d; // store event weight in array
    n_count++; // increase counters by one
    w_count++;
  }

  input_file.close(); // close file one

  for (int i = 0; i < w_count; i++) // calculate threshold by adding all event weights
  {
    threshold += event_weight_array[i];
  }

  threshold = threshold * 2; // multiply sum of weights by 2

  input_file.open(argv[2]); // open second file

  if (!input_file) // if file not found send error, exit program
  {
    std::cerr << "No file found. Exiting program..." << std::endl;
    return -1;
  }
  else // else file found
  {
    std::cout << "File found..." << std::endl;
  }

  while (std::getline(input_file, measure_event1, ':')
  && std::getline(input_file, measure_event2, ':')
  && std::getline(input_file, measure_event3, ':')
  && std::getline(input_file, measure_event4, ':')
  && std::getline(input_file, measure_event5, ':'))
  {

    measure_event_d = std::stod(measure_event1); // convert respective measure event string to double
    measure_event_array[me_count] = measure_event_d; // store in measure event array
    me_count++; // increase count of number of monitored events

    measure_event_d = std::stod(measure_event2);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event3);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event4);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event5);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    if (me_count == n_count) // if number of measure events equals number of event names
    {
      for (int j = 0; j < n_count; j++) // add measured event to respective position in array
      {
        event_average[j] = event_average[j] + measure_event_array[j];
      }

      max_me_count++; // increase number of lines
      me_count = 0; // number of monitored events set to 0 for next line of measured events
    }

  }

  input_file.close();

  for (int j = 0; j < n_count; j++) // divide sum for each event by number of events
  {
    event_average[j] = event_average[j]/max_me_count; // event average obtained
  }

  me_count = 0; // number of monitored events set to 0 for standard deviation calculation

  input_file.open(argv[2]); // open second file again

  while (std::getline(input_file, measure_event1, ':')
  && std::getline(input_file, measure_event2, ':')
  && std::getline(input_file, measure_event3, ':')
  && std::getline(input_file, measure_event4, ':')
  && std::getline(input_file, measure_event5, ':'))
  {
    measure_event_d = std::stod(measure_event1); // convert respective measure event string to double
    measure_event_array[me_count] = measure_event_d; // store in measure event array
    me_count++; // increase count of number of monitored events

    measure_event_d = std::stod(measure_event2);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event3);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event4);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event5);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    if (me_count == n_count)
    {

      for (int j = 0; j < n_count; j++) // add the sum of (measured event - variance)^2 of each event
      {
        event_stdev[j] = event_stdev[j] + std::pow((measure_event_array[j] - event_average[j]),2);
      }

      me_count = 0; // number of monitored events set to 0 for next line of measured events

    }

  }

  input_file.close(); // close second file again

  for (int j = 0; j < n_count; j++) // square root the summed (measured event - variance)^2 divide by number of lines
  {
    event_stdev[j] = std::sqrt(event_stdev[j]/max_me_count); // standard deviation obtained
  }

  std::cout << std::left <<  std::setw(25) << "\nEvent " << std::setw(20)
  << " Average " << std::setw(20)
  << " Stdev " << std::setw(20)
  << " Weight " << '\n' << '\n';

  for (int j = 0; j < n_count; j++) // print information for each event
  {
    std::cout << std::left << std::setw(25) << name_array[j] << ": " << std::setw(20)
    << std::fixed << std::setprecision(2) << event_average[j] << std::setw(20)
    << std::setprecision(2) << event_stdev[j];
    std::cout << std::setw(20) << event_weight_array[j] << '\n';

  }

  std::cout << "\nThreshold: " << threshold << std::endl; // print threshold
  std::cout <<"\n";

  me_count = 0; // set measured event count to 0 for later use

  input_file.open(argv[3]); // open third file

  while (std::getline(input_file, measure_event1, ':')
  && std::getline(input_file, measure_event2, ':')
  && std::getline(input_file, measure_event3, ':')
  && std::getline(input_file, measure_event4, ':')
  && std::getline(input_file, measure_event5, ':'))
  {
    measure_event_d = std::stod(measure_event1); // convert respective measure event string to double
    measure_event_array[me_count] = measure_event_d; // store in measure event array
    me_count++; // increase count of number of monitored events

    measure_event_d = std::stod(measure_event2);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event3);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event4);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    measure_event_d = std::stod(measure_event5);
    measure_event_array[me_count] = measure_event_d;
    me_count++;

    std::cout << std::left << std::setw(10) << "Line " << line_count << " -- "
    << measure_event1 << ":" << measure_event2 << ":"
    << measure_event3 << ":" << measure_event4 << ":"
    << measure_event5 << ": " << std::setw(10);


    for (int j = 0; j < n_count; j++) // add to distance the calculation
    { //((measured event - event average)/event standard deviation) * weight summing all events
      distance = distance + std::abs(((measure_event_array[j] - event_average[j])/event_stdev[j]) * event_weight_array[j]);
    }

    if (distance > threshold) // if the distance is greater than the threshold, raise the alarm
    {
      std::cout << std::left << std::setw(15) << " Distance: " << std::setw(15) << distance
      << std::setw(15) << " Alarm: Yes\n" << std::endl;
    }
    else // else no alarm
    {
      std::cout << std::left << std::setw(15) << "Distance: " << std::setw(15) << distance
      << std::setw(15) << " Alarm: No\n" << std::endl;
    }

    distance = 0; // reset distance to 0 for each line
    me_count = 0; // reset measured events to 0 for each line
    line_count++; // increase number of lines

  }

  input_file.close(); // close third file

  return 0; // complete main
}
