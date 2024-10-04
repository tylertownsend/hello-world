#include <mpi.h>
#include <iostream>
#include <vector>

using namespace std;

// Function to perform the matrix multiplication using MPI
vector<vector<int>> mat_mult(const vector<int>& A, const vector<int>& B, int N);
void print_matrix(const vector<int>& A, int cols);
void initialize_matrix(vector<int>& A, vector<int>& B, int N);

int main(int argc, char *argv[]) {
  int world_rank, world_size;

  // Initialize the MPI environment
  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);

  const int N = 4; // Assuming a 4x4 matrix and 4 MPI processes

  // Initialize matrices A and B with some values
  vector<int> A(N * N), B(N * N);

  // Only rank 0 initializes the matrices
  if (world_rank == 0) {
    initialize_matrix(A, B, N);
  }

  // Perform matrix multiplication
  vector<vector<int>> C = mat_mult(A, B, N);

  // Rank 0 prints the result
  if (world_rank == 0) {
    cout << "\nMatrix C (Result of A * B):" << endl;
    for (const auto& row : C) {
      for (int val : row) {
        cout << val << " ";
      }
      cout << endl;
    }
  }

  // Finalize the MPI environment
  MPI_Finalize();
  return 0;
}

vector<vector<int>> mat_mult(const vector<int>& A, const vector<int>& B, int N) {
    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    vector<int> C(N * N, 0); // Flat vector for result
    vector<int> A_row(N, 0), C_row(N, 0); // For individual rows that are given to the processes

    // Broadcast matrix B to all processes
    MPI_Bcast((void*)B.data(), N * N, MPI_INT, 0, MPI_COMM_WORLD);

    // Scatter rows of matrix A to each process
    MPI_Scatter((void*)A.data(), N, MPI_INT, A_row.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    // Perform the multiplication for the assigned row
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        C_row[i] += A_row[j] * B[j * N + i];
      }
    }

    // Gather the results from all processes to process 0
    MPI_Gather(C_row.data(), N, MPI_INT, C.data(), N, MPI_INT, 0, MPI_COMM_WORLD);

    // Convert the flat result vector to a 2D vector
    vector<vector<int>> C_2D(N, vector<int>(N));
    if (world_rank == 0) {
      for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
          C_2D[i][j] = C[i * N + j];
        }
      }
    }

    return C_2D;
}

void print_matrix(const vector<int>& A, int cols) {
  for (int i = 0; i < A.size(); i++) {
    std::cout << A[i];
    if ((i + 1) % cols == 0) {
      std::cout << "\n";
    } else {
      std::cout << ", ";
    }
  }
}

void initialize_matrix(vector<int>& A, vector<int>& B, int N) {
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      A[i * N + j] = i + j; // Any initialization logic
      B[i * N + j] = i + j; // Any initialization logic
    }
  }
  std::cout << "\nMatrix A:\n";
  print_matrix(A, N);
  std::cout << "\nMatrix B:\n";
  print_matrix(B, N);
}
