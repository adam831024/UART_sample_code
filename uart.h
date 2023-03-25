#ifndef _UART_H_
#define _UART_H_

  #include <stdint.h>
  #include <stdlib.h>

/*****************************************************************************/

  /**
   * \fn int com_init(int BaudRate)
   * \brief Enumerate all the port and connect with a specific baudrate
   * \param[in] baudrate port baudrate
   * \return return index if success, return 0xFFFF if fail
   */       
  int com_init(int BaudRate);

  /**
   * \fn pthread_t com_read(int index)
   * \brief Open a thread to read data from the port
   * \param[in] index port index
   * \return Thread ID if success, do not return if fail
   */    
  pthread_t com_read(int index);

  /**
   * \fn void com_write(int index)
   * \brief Write data to the port
   * \brief If write data isn't HEX type, exit loop
   * \param[in] index port index
   */    
  void com_write(int index);

  /**
   * \fn void com_close(int index, pthread_t t )
   * \brief Close an opened port and thread
   * \param[in] index port index
   * \param[in] Thread ID of com_read
   */    
  void com_close(int index, pthread_t t );
/*****************************************************************************/
#endif