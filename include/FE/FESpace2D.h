// =======================================================================
// @(#)FESpace2D.h        1.5 06/13/00
// 
// Class:       TFESpace2D
// Purpose:     class for all 2D finite element spaces
//
// Author:      Gunar Matthies (03.11.97)
//
// History:     start of implementation 03.11.97 (Gunar Matthies)
//
//              split FESpace into TFESpacexD
//              15.04.1998 (Volker Behns)
//
//              start of reimplementation
//              30.07.98 (Gunar Matthies)
//
// =======================================================================

#ifndef __FESPACE2D__
#define __FESPACE2D__

#include <FESpace.h>
#include <FE2D.h>

class THangingNode;

/** class for all 2D finite element spaces */
class TFESpace2D : public TFESpace
{
  protected:
    /** number of active degrees of freedom */
    int N_ActiveDegrees;

    /** number of slave degrees of freedom */
    int N_SlaveDegrees;

    /** NeumannBound <= i < HangingBound for all hanging nodes i */
    /** => HangingBound <= i < DirichletBound for all Dirichlet node i */
    int HangingBound;

    /** array containing the used elements */
    FE2D *UsedElements; 


    /** array with an element for each shape */
    FE2D *ElementForShape;

    /** array of hanging nodes */
    THangingNode **HangingNodeArray;

    /** array storing the fe for each element, if necessary */
    FE2D *AllElements;
    
    /** boundary condition used to create this space */
   BoundCondFunct2D *BoundCondition;

   /** Store Reference Transformation of all the cells **/


#ifdef __MORTAR__
    /** 1D collection of mortar cells */
    TCollection *MortarColl;
#endif

   /** no. points in internal coordinate direction --- ADI scheme*/
   int N_IntlPts;

   /** internal points' X coordinate --- ADI scheme*/
   double *X_Intl;

   /** internal points' Y coordinate --- ADI scheme*/
   double *Y_Intl;

   /** indices for mapping between Nodalfunctional/Nodal-interpolation point 
      in operator-splitting methods ---  Sashikumaar Ganesan */
   int *IntlPtIndexOfPts;

  // Implemented by Thivin - June 2022
  // THis was started to make sure that all the TReftrans pointers to all class are saved seperately for each cell 
  // This enables the parallel FE computation of all the threads without having to rely on the static datastructure used for reftrans. 
  // Warning, If you are tying to use the below pointers to compute the FE calculations , make sure to 
  //      -- Check whether the function is virtual in the Base class(TReftrans2D)
  //      -- Chech the implementation of that function in the derived class.
  
  /** Store all the reference transformation Objects of the cells using the baseclass pointer TReftrans2D **/
  RefTrans2D*  RefTrans2DArray;

  /** Store all the reference transformation Objects of the cells using the baseclass pointer, which is TReftrans2D **/
  TRefTrans2D** TRefTrans2DArray;

  // Implementation by Thivin -- End 

  public:
    /** constructor */
    TFESpace2D(TCollection *coll, char *name, char *description);

    /** constructor for building a space with elements of order k */
    // if no mortar is used, the last argument can be set to NULL
    TFESpace2D(TCollection *coll, char *name, char *description, 
               BoundCondFunct2D *BoundaryCondition, int k,
               TCollection *mortarcoll);

    TFESpace2D(TCollection *coll, char *name, char *description, 
               BoundCondFunct2D *BoundaryCondition, SpaceType type,
               int k, TCollection *mortarcoll);

    /** constructor for building a space with the given elements */
    TFESpace2D(TCollection *coll, char *name, char *description,
               BoundCondFunct2D *BoundaryCondition,
               FE2D *fes, TCollection *mortarcoll);

    // Implemented by Thivin - Jun 2022
    // THis function will Store the corresponding Reftrans pointers to all the cells in the TRefTrans2DArray 
    // This function should be called during the constructor of FESpace2D 
    void StoreRefTrans();

    //THIVIN 
    // This function is a getter function to obtain the reftrans of the given aray 
    
    /** Returns the stored TReftrans2D for the given Cell number */
    TRefTrans2D* getTRefTrans2DforCell(int cellNumber) {
      return TRefTrans2DArray[cellNumber];
    }

    /** Returns the stored Reftrans2D for the given Cell number */
    RefTrans2D getRefTrans2DforCell(int cellNumber) {
      return RefTrans2DArray[cellNumber];
    }
    /** destructor */
    ~TFESpace2D();

    /** find used elements */
    void FindUsedElements();

    /** construct space */
    void ConstructSpace(BoundCondFunct2D *BoundaryCondition);

    /** return number of active degrees of freedom */
    int GetN_ActiveDegrees() const
    { return N_ActiveDegrees; }

    /** return number of slave degrees of freedom */
    int GetN_SlaveDegrees() const
    { return N_SlaveDegrees; }

    /** return HangingBound */
    int GetHangingBound() const
    { return HangingBound; }

    /** return N_Hanging=N_SlaveDegrees */
    int GetN_Hanging() const
    { return N_SlaveDegrees; }

    /** return identifiers of used elements */
    FE2D *GetUsedElements() const
    { return UsedElements; }

    /** return array with all hanging nodes */
    THangingNode **GetHangingNodes() const
    { return HangingNodeArray; }

    /** return the FE Id for element i, corresponding to cell */
    FE2D GetFE2D(int i, TBaseCell *cell);

    /** return position of one given DOF */
    void GetDOFPosition(int dof, double &x, double &y);

    /** return position of all dofs */
    void GetDOFPosition(double *x, double *y);

    void GetDOFPosition(double *x, double *y,int* cellNo);

    /** return DOF number of the given Position **/
    int GetDOFNumberfromPosition(int DOF, double x,double y );

    void SetIntlPtIndexOfPts(int *intlPtIndexOfPts)
     { IntlPtIndexOfPts = intlPtIndexOfPts; }

    int *GetIntlPtIndexOfPts() const
     { return IntlPtIndexOfPts; }
     
     FE2D *GetAllElements() const
     { return AllElements; }
     
     /** return boundary condition */
    BoundCondFunct2D *GetBoundCondition() const
    { return BoundCondition; }
    
    friend  bool operator== (const TFESpace2D &lhs, const TFESpace2D &rhs);
    friend  bool operator!= (const TFESpace2D &lhs, const TFESpace2D &rhs);
};

#ifdef __MORTAR__
  double GetLambda(double , double , TVertex *, double , double );
#endif // __MORTAR__

#endif
