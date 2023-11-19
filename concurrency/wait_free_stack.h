
template<typename T>
class lock_free_stack {
private:
  struct node {
    T data;
    node* next;
    node(const T& data_):
      data(data_) {}
  }

  struct stack_descriptor {
    node* head;
  };

  

public:
};