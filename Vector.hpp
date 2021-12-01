/**
 * @class Vector
 * @brief Es una estructura de datos basada en arreglo dinámico
 */
template <class T>
class Vector {
  private:
    // potencial arreglo de datos de tipo genérico
    T* m_data;
    // alacenamiento total
    size_t m_capacity;
    // número de elementos actuales
    size_t m_size;

    void resize();

//bool operator==() y  bool operator!=() // comparan el contenido de los vectores así como su tamaño (size)
  public:
    Vector();
    Vector(const size_t& p_cap);
    Vector(Vector& p_v1);
    Vector(Vector* p_v1);
    Vector(const T p_arr[], const size_t& p_arrSize);
    size_t capacity();
    size_t size();
    T at(const size_t& p_index);
    void push_back(T p_elem);
    void pop_back(); // Elimina el último elemento
    void shrink_to_fit(); // Ajusta el tamaño de data (m_capacity = m_size)
    void push_front(T p_elem);
    T& operator[](const size_t& p_index);
    bool operator==(Vector& p_compare);
    Vector<T>& operator=(Vector& p_v);
};

/**
 * Cambia el tamaño del arreglo duplicando su capacidad
 * 
 */
template <class T>
Vector<T>::Vector() {
  m_data = new T[1];
  m_capacity = 1;
  m_size = 0;
}

/**
 * Cambia el tamaño del arreglo duplicando su capacidad
 * @param p_cap la capacidad inicial del vector
 */
template <class T>
Vector<T>::Vector(const size_t& p_cap) {
  m_data = new T[p_cap];
  m_capacity = p_cap;
  m_size = 0;
}

/**
 * Crea un vector con una copia de los elementos de otro
 * @param v1 es el vector con los elementos orinales
 */
template <class T>
Vector<T>::Vector(Vector<T>& p_v1) {
  m_data = new T[p_v1.capacity()];
  m_capacity = p_v1.capacity();
  m_size = p_v1.size();
  for (int i = 0; i < m_size; i++) {
    m_data[i] = p_v1.at(i);
  }
}

/**
 * Crea un vector como copia de la referencia
 * @param v1 es el vector con los elementos orinales
 */
template <class T>
Vector<T>::Vector(Vector<T>* p_v1) {
}

/**
 * Crea un vector con una copia de los elementos de otro
 * @param v1 es el vector con los elementos orinales
 */
template <class T>
Vector<T>::Vector(const T p_arr[], const size_t& p_arrSize) {
  m_data = new T[p_arrSize];
  m_capacity = p_arrSize;
  m_size = p_arrSize;
  for (int i = 0; i < m_size; i++) {
    m_data[i] = p_arr[i];
  }
}

/**
 * Devuelve la capacidad de data
 * 
 */
template <class T>
size_t Vector<T>::capacity() {
  return m_capacity;
}

/**
 * Devuelve el número de elementos que hay en data
 * 
 */
template <class T>
size_t Vector<T>::size() {
  return m_size;
}

/**
 * Devuelve una copia del dato en el índice dado
 * @param index es el índide del que se quiere copiar el dato
 * @throw out_of_range si el índice es menor a cero, o mayor al size
 */
template <class T>
T Vector<T>::at(const size_t& p_index) {
  if (p_index >= m_size) {
    throw std::out_of_range("Índice fuera del rango");
  }
  return m_data[p_index];
}

/**
 * Agrega un elemento al final del arreglo, y si se queda
 * sin espacio llama a @reference resize
 */
template <class T>
void Vector<T>::push_back(T p_elem) {
  if (m_capacity == m_size) {
    resize();
  }
  m_data[m_size] = p_elem;
  m_size++;
}

/**
 * Cambia el tamaño del arreglo duplicando su capacidad
 * 
 */
template <class T>
void Vector<T>::resize() {
  T* tmp = new T[m_capacity];
  for (int i = 0; i < m_capacity; i++) {
    tmp[i] = m_data[i];
  }
  delete[] m_data;
  // Estos detalles son lo que hace importate crear tus propias estucturas de datos
  m_capacity *= 2; 
  m_data = new T[m_capacity];
  for (int i = 0; i < m_capacity; i++) {
    m_data[i] = tmp[i];
  }
  delete[] tmp;
}

/**
 * Sobrecarga que nos permite acceder a la referencia en el índice dado 
 * @param index índice al que se quiere acceder
 * @return referencia al elemento el el índice indicado
 * @throw std::out_of_range se arroja en el caso de que el índice sea mayor que el m_size
 */
template <class T>
T& Vector<T>::operator[](const size_t& p_index) {
  if (p_index >= m_size) {
    throw std::out_of_range("Índice fuera del rango");
  }
  return m_data[p_index];
}

/**
 * Elimina el último elemento del arreglo
 * 
 */
template <class T>
void Vector<T>::pop_back() {
  if (m_size == 0) {
    return;
  }
  m_size--;
}

/**
 * Cambia el tamaño del arreglo: capacidad = size
 * @throw exception en caso de que ya está fit, o m_capacity = 0 
 */
template <class T>
void Vector<T>::shrink_to_fit() {
  if ((m_capacity == m_size) || (m_capacity == 0)) {
    throw std::domain_error("Ya no se puede fitear");
  }
  T* tmp = new T[m_size];
  for (int i = 0; i < m_size; i++) {
    tmp[i] = m_data[i];
  }
  delete[] m_data;
  m_capacity = m_size; 
  m_data = new T[m_capacity];
  for (int i = 0; i < m_capacity; i++) {
    m_data[i] = tmp[i];
  }
  delete[] tmp;
}

/**
 * Incerta un elemento al inicio del vector, por contraintuitivo que sea
 * @throw exception en caso de que ya está fit, o m_capacity = 0 
 */
template <class T>
void Vector<T>::push_front(T p_elem) {
  if ((m_capacity == m_size) || (m_capacity == 0)) {
    resize();
  }
  for (int i = m_size; i > 0; i--) {
    m_data[i-1] = m_data[i];
  }
  m_data[0] = p_elem;
  m_size++;
}

/**
 * Sobrecarga que nos permite compara el contenido de dos vectores 
 * @param p_compare vector a compara con el actual
 * 
 */
template <class T>
bool Vector<T>::operator==(Vector<T>& p_compare) {
  if (m_size != p_compare.size()) {
    return false;
  }
  for (int i = 0; i < m_size; i++) {
    if (m_data[i] != p_compare.at(i)) {
      return false;
    }
  }
  return true;
}

/**
 * Sobrecarga que nos permite asignar un vector a otro
 * @param p_v vector a asignar en el actual
 * example: Vector v = {1,2}, Vector v2 = {3,4,5}
 * v = v2; // v = {3,4,5}
 */
template <class T>
Vector<T>& Vector<T>::operator=(Vector<T>& p_v) {
  delete m_data;
  m_size = p_v.size();
  m_capacity = p_v.capacity();
  m_data = new T[m_capacity];
  for (int i = 0; i < m_size; i++) {
    m_data[i] = p_v[i];
  }
  return *this;
}