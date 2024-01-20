#ifndef MTA_IO_CLIENT_COMMON_MTA_IO_CLIENT_HPP
#define MTA_IO_CLIENT_COMMON_MTA_IO_CLIENT_HPP
#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>
#include <map>
#include <time.h>
#include <cstdio>

/**
  @brief Data format used for sending and receiving IO samples
  The io_base array stores the sample data for each port, where each port
  is split into multiple bytes. The mapping from io_base array to the
  physical ports is as follows:
    io_base[0] : Port 0-7
    io_base[1] : Port 7-15
    io_base[2] : Port 16-23
    io_base[3] : Port 23-31
    io_base[4] : Port 32-39
    io_base[5] : Port 40-48
    io_base[6] : Port 48-55
    io_base[7] : Port 56-63
    io_base[8] : Port 64-71
    io_base[9] : Port 72-79
    io_base[10] : Port 80-83
    io_base[11] : Not used
    io_base[12] : ADC1 Port 0-7
    io_base[13] : ADC1 Port 8-11
    io_base[14] : ADC2 Port 0-7
    io_base[15] : ADC2 Port 8-11
*/
#define LENGTH_SAMPLES_BYTES 16
typedef struct mta_io_sample {
  uint8_t io_base[LENGTH_SAMPLES_BYTES];

  const char* data() const {
    return reinterpret_cast<const char*>(&io_base[0]);
  }

  char* get_raw_data() {
    return reinterpret_cast<char*>(&io_base[0]);
  }

  operator char*() {
    return reinterpret_cast<char*>(&io_base[0]);
  }

  int size() const {
    return LENGTH_SAMPLES_BYTES;
  }
} mta_io_sample_t;


/**

  @brief Struct containing a mask for configuring the input/output ports of the FPGA.
    This struct contains a mask for configuring the input/output (I/O) ports of the FPGA. 
    It contains a vector of 32-bit unsigned integers that represent the port mask for each 
    group of ports on the FPGA. 
    Each bit in the mask represents a single I/O port, with a value 
    of 0 indicating that the port is configured as an input port and a value of 1 indicating 
    that the port is configured as an output port.

  The mask is organized as follows:
      mask[0]: Ports 0-31
      mask[1]: Ports 32-63
      mask[2]: Ports 64-83
  The values in the mask correspond to the pointer to the FPGA address.
*/
typedef struct io_mask {
  std::vector<uint32_t> mask = {0,0,0}; /* following pointer fpga address  */
} io_mask_t;


/**
  @brief Enumeration of possible states of the FPGA IO system.
  This enumeration lists the possible states of the FPGA IO system, which can
  be one of the following: 
  IO_IDLE: The system is available for configuration and IO sample data transfer. 
  IO_RUNNING: The system is currently transferring IO sample data. 
  IO_FORCE_PAUSE: The system is waiting for a forced pause command to be issued. 
  IO_UNKNOWN: The system is not available for starting IO sample data transfer.
*/
enum io_state { IO_IDLE = 0, IO_RUNNING = 1, IO_FORCE_PAUSE, IO_UNKNOWN };

  
/* ======================== New API ============================= */

/**
  @brief Sets the HTTP base URL to be used for subsequent API requests.
  This function sets the HTTP base URL to be used for subsequent API requests.
  @param baseUrl A C-string representing the base URL to be set.
  @param timeout_ms A unsigned integer representing the timeout to connect URL 
  @return An integer representing the success/failure of the configuration
  process. A return value of 0 indicates success, while a non-zero value
  indicates failure if baseURL is NULL pointer.
*/
int set_baseUrl(const char* baseUrl, uint32_t timeout_ms);


/**
  @brief Configures the input/output IOport, clock settings and sample_units for the FPGA.
  This function configures the input/output port and clock settings for the
  FPGA based on the given parameters. 
  @param mask_io A bitmask used to configure the input/output ports.
  @param clock_divisor A value used to configure the clock divisor, which
  divides the base clock with a frequency of 120MHz. The resulting frequency
  is calculated as follows:
  hw_frequency = 120MHz / (clock_divisor + 1)
  @param sample_units A value used to configure the number of sample units for
  continuous sampling. For example, if there are 8192 samples and the sample
  units are set to 1024, the FPGA will present DMA transfer 8 times with 1024
  samples each time.
  @param clk_source Select clock clk_source  internal(0)/external(1) (MUST BE 0 OR 1)
  @param clk_io_mask Select OUTPUT clock mask for extern clock output.
  @return An integer representing the success/failure of the configuration
  process. A return value of 0 indicates success, while a non-zero value
  indicates failure.
  @note This function assumes that the FPGA is properly initialized and
  configured.
  @note The mask_io parameter must be a valid bitmask, otherwise the function
  will fail.
  */
int io_set_config(io_mask mask_io, uint32_t clock_divisor, uint32_t sample_units);
int io_set_config(io_mask mask_io, uint32_t clock_divisor, uint32_t sample_units, 
                uint32_t clk_source, io_mask clk_io_mask);


/**
  @brief Sets the sample data for the output_sample parameter.
  This function sets the sample data for the output_sample parameter using the
  data from the input_samples parameter.
  @param output_sample Pointer to the output sample structure to set the
  sample data for write to IO. (Need allocated before)
  @param input_samples Pointer to an array of input sample structures
  containing the sample data from IO. (Need allocated before)
  @param numb The number of input samples in the output_sample array.
  @param is_sync A flag indicating whether the input samples are synchronous.
  Return imediately when is_sync=0, if is_sync=1 it will wait to success
  receive data.
  @return An integer representing the success/failure of the configuration
  process. A return value of 0 indicates success, while a non-zero value
  indicates failure.
  @note This function assumes that the output_sample and input_samples arrays
  are properly allocated and initialized.
  @note The input_samples array must contain at least one sample, otherwise
  the software could be segmentation fault when has valid data from IO input.
  @note If the is_sync flag is set to true, the sample rate of the
  output_sample will be set to the sample rate of the first input sample.
*/
int io_set_sample_data(mta_io_sample_t* output_sample, mta_io_sample_t* input_samples, uint32_t numb, uint32_t is_sync);

/**

  @brief Gets input/output sample data from the FPGA.
  This function retrieves input/output sample data from the FPGA using the
  given input_samples buffer and the maximum number of samples to receive,
  which is limited by the numb_limited_sample parameter.
  @param input_samples Pointer to the buffer to store the input/output sample
  data received from the FPGA.
  @param numb_limited_sample The maximum number of samples to receive from the
  FPGA. If the number of samples received exceeds numb_limited_sample, the
  excess samples will be discarded.
  @return An integer representing the success/failure of the data retrieval
  process. A return value indicates the size of sample received, return -1 when failed.  
  @note This function assumes that the FPGA is properly initialized and
  configured.
  @note The input_samples buffer must be properly allocated and initialized
  before calling this function.
  @note The number of samples to receive (numb_limited_sample) must be less
  than or equal to the size of the input_samples buffer to safe software.
  */
int io_get_sample_data(mta_io_sample_t* input_samples, uint32_t numb_limited_sample);

/**

  @brief Gets the status of the FPGA boards.
  This function retrieves the status of the FPGA boards and returns it as an
  enumerated value of the io_state type.
  @param status Reference to a uint32_t variable to store the status of the
  FPGA boards. The status is returned as an enumerated value of the io_state
  type.
  @return An integer representing the success/failure of the status retrieval
  process. A return value of 0 indicates success, while a non-zero value
  indicates failure.
  @note This function assumes that the FPGA boards are properly initialized
  and configured.
  */
int io_get_status(uint32_t& status);

/**

  @brief Forces the transfer of IO sample data to pause.
  This function forces the transfer of IO sample data to pause.
  @return An integer representing the success/failure of the pause command. A
  return value of 0 indicates success, while a non-zero value indicates
  failure.
  @note This function assumes that the FPGA is properly initialized and
  configured.
  */
int io_pause();

/**
  @brief Sends data over UART and receives response data.
  This function sends data over UART using the given data_write buffer and the
  number of bytes to send. It also receives any response data using the given
  data_read buffer and the maximum number of bytes to receive.
  @param data_write Pointer to the buffer containing the data to send over
  UART. (Need to allocated before)
  @param numb_byte_to_sent The number of bytes to send over UART.
  @param data_read Pointer to the buffer to store any response data received
  over UART. (Need to allocated before)
  @param max_byte_to_receive The maximum number of bytes to receive over UART store in `data_read` buffer.
  @return An integer representing the success/failure of the UART
  transmission. Return the size of data read if sucess, and return -1 when failed to trasnfer.
  @note This function assumes that the UART is properly initialized and
  configured.
  @note The data_write and data_read buffers must be properly allocated and
  initialized before calling this function.
  @note The number of bytes to send (numb_byte_to_sent) must be less than or
  equal to the size of the data_write buffer.
  @note The maximum number of bytes to receive (max_byte_to_receive) must be
  less than or equal to the size of the data_read buffer.
  */
int uart_sent_data(char* data_write, uint32_t numb_byte_to_sent, char* data_read, uint32_t max_byte_to_receive);
int uart_sent_data(char* data_write, uint32_t numb_byte_to_sent, char* data_read, uint32_t max_byte_to_receive, uint32_t timeout_ms);



#endif