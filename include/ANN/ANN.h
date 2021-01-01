// =======================================================================
// @(#)TANN.h        1.0 24.12.20
// 
// Class:       TANN
// Purpose:     Class for Artificial Neural Networks (ANN) - Base class
//
// Author:      Subodh M. Joshi (24.12.20)
//
// History:     start of implementation 24.12.20 (Subodh M. Joshi)
//
// =======================================================================

#ifndef __TANN__
#define __TANN__

#include <ANNIncludes.h>
#include <ANNLayer.h>

/** Class for artificial neural networks (ANN) **/
class TANN
{
  public:
  /** constructor 1 */  
  TANN();

  /** constructor 2 */
  TANN(TANNParamReader *paramReader);

  /** destrcutor */
  ~TANN();

  public:
  /** Data members */

  TANNLayer* layers; // array storing individual layers

  int nHL;  // number of hidden layers

  int nLayers; // total number of layers

  mlpack::ann::FFN<> model; // mlpack model for feed forward network



  private:
  /** Flags */
  bool layerFlag;
  bool modelFlag;

};

#endif
