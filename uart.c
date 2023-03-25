#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "rs232.h"

/*****************************************************************************/
int str2Hex( char pstr)
{
  int ans = 0;
  char pt;
  pt = pstr;
  if( !pstr )
    return 0;
  else
  {       
    if( ( pt >=  'A' && pt <=  'F' ) || ( pt >=  'a' && pt <=  'f' ) )
      ans  = ((pt & 0x5f) -0x37);
    else if( pt >= '0' && pt <= '9')
      ans  = (pt) -0x30;
    else
      ans = 0x00;
    return ans;
  }
}

/*****************************************************************************/
int com_init(int BaudRate)
{
  uint8_t n;
  uint8_t COM[6];
  uint8_t index;

  n = comEnumerate();
  printf("comEnumerate = %d\n",n );

  printf("==========================\n");

  for(int i=0;i<n;i++)
  {
    memcpy(COM, comGetPortName(i), sizeof(COM));
    printf("index: %d = %s\n",i,COM );
  }

  printf("==========================\n");

  printf("Plaese input a index to open com port: ");
  scanf("%d",&index);

  printf("==========================\n");
  n = comOpen(index, BaudRate);
  if(!n)
  {
    printf("COM port open fail\n");
    return 0xFFFF; //error index 
  }
  else
  {
    printf("%s open success\n",comGetPortName(index));
    return index;
  }
}

/*****************************************************************************/
void* com_read_child (void* param)
{
  int n;
  uint8_t *index = param;
  uint8_t rxBuf[50];
  // pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
  while(1)
  {

    n = comRead(*index, rxBuf, sizeof(rxBuf));

    if(n==-1)
    {
      break;
    }
    else if(n && n != -1)
    {
      printf("==========================\n");

      for(int j = 0; j < n; j++)
      {
        printf("rxBuf[%d] = 0x%x\n", j, rxBuf[j]);
      }

      printf("comRead success return %d bytes.\n",n );

      printf("==========================\n");
    }
  }
}

/*****************************************************************************/
pthread_t com_read(int index)
{
  if (index != 0xFFFF)
  {
    pthread_t t;
    pthread_create(&t, NULL, com_read_child, &index);
    return t;
  }
  else
    printf("com_read fail\n");
}

/*****************************************************************************/
void com_write(int index)
{
  if (index != 0xFFFF)
  {
    uint8_t txBuf_tmp[10];
    uint8_t len;
    uint8_t txBuf[10];
    uint8_t n;

    while(1)
    {
      scanf("%s",txBuf_tmp);

      if (txBuf_tmp[0] < '0' || txBuf_tmp[0] > '9' && txBuf_tmp[0] < 'A' || txBuf_tmp[0] > 'F' && txBuf_tmp[0] < 'a' || txBuf_tmp[0] > 'f')
      {
        break;
      }
      else
      {
        len = strlen(txBuf_tmp);
        for(int i = 0; i < (len/2); i++)
        {
          txBuf[i] = (str2Hex(txBuf_tmp[i*2])<<4) + (str2Hex(txBuf_tmp[i*2+1]) );
        }

        n = comWrite(index, txBuf,(len/2));
        printf("comWrite success return %d bytes.\n",n );
      }
    }
  }
  else
    printf("com_write fail\n");
}
/*****************************************************************************/
void com_close(int index, pthread_t t )
{
  if (index != 0xFFFF)
  {
    printf("com port closing\n");
    comClose(index);     
    pthread_join(t, NULL);
    printf("close complete\n");  
    
  }  
  else
    printf("com_close fail\n");
}

/*****************************************************************************/
