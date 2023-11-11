#include <mpi.h>
#include <iostream>
#include <vector>
#include <algorithm>

// Function to merge two sorted vectors
std::vector<int> merge(const std::vector<int>& left, const std::vector<int>& right) {
  std::vector<int> result;
  unsigned left_it = 0, right_it = 0;

  while (left_it < left.size() && right_it < right.size()) {
    if (left[left_it] < right[right_it]) {
      result.push_back(left[left_it]);
      left_it++;
    } else {
      result.push_back(right[right_it]);
      right_it++;
    }
  }

  // Append remaining elements
  while (left_it < left.size()) result.push_back(left[left_it++]);
  while (right_it < right.size()) result.push_back(right[right_it++]);

  return result;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);

  int world_size;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  int world_rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  const int N = 100; // Size of the array to sort
  std::vector<int> data;

  // Root process generates the data
  if (world_rank == 0) {
    data.resize(N);
    std::generate(data.begin(), data.end(), []() { return std::rand() % 100; });
  }

  // Determine the size of the subarray for each process
  int size = N / world_size;
  std::vector<int> sub_data(size);

  // Scatter the random numbers to all processes
  MPI_Scatter(data.data(), size, MPI_INT, sub_data.data(), size, MPI_INT, 0, MPI_COMM_WORLD);

  // Each process sorts its subarray
  std::sort(sub_data.begin(), sub_data.end());

  // Gather the sorted subarrays at the root process
  std::vector<int> sorted_data;
  if (world_rank == 0) {
      sorted_data.resize(N);
  }
  MPI_Gather(sub_data.data(), size, MPI_INT, sorted_data.data(), size, MPI_INT, 0, MPI_COMM_WORLD);

  // Merge the subarrays at the root process
  if (world_rank == 0) {
    std::vector<int> temp;
    std::vector<int> merged = sorted_data;

    for (int i = 1; i < world_size; i++) {
      temp.assign(sorted_data.begin() + i * size, sorted_data.begin() + (i + 1) * size);
      merged = merge(merged, temp);
    }

    // Print the sorted array
    for (int num : merged) {
      std::cout << num << " ";
    }
    std::cout << std::endl;
  }

  MPI_Finalize();
  return 0;
}
