// ======================================================================
// Sine problem
// ======================================================================

#include <MacroCell.h>
#include <IsoBoundEdge.h>
#include <IsoInterfaceJoint.h>
#include <MacroCell.h>
#include <IsoBoundEdge.h>
#include <IsoInterfaceJoint.h>
#include <QuadAffin.h>
#include <FEDatabase2D.h>
#include <FEFunction2D.h>
#include <NodalFunctional2D.h>
#include <AllRefTrans.h>
#include <sstream>
#include <vector>
// #include <AllNodalFunctionals2D.h>

extern "C"
{
#include <gridgen.h>

	void triangulate(char *, struct triangulateio *,
					 struct triangulateio *, struct triangulateio *);
}

void ExampleFile()
{
	OutPut("Example: SineLaplace.h" << endl);
}

// exact solution
void Exact(double x, double y, double *values)
{
	values[0] = 0;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;
}

void InitialCondition(double x, double y, double *values)
{
	double t;

	t = TDatabase::TimeDB->CURRENTTIME;
	values[0] = 0;
}

// kind of boundary condition (for FE space needed)
void BoundCondition(int BdComp, double t, BoundCond &cond)
{

	cond = DIRICHLET;
}

// value of boundary condition
void BoundValue(int BdComp, double Param, double &value)
{
	static double eps = 1 / TDatabase::ParamDB->PE_NR;

	if (BdComp == 2)
	{
		if (fabs(Param - 0.0) < 1e-8 || fabs(Param - 1.0) < 1e-8)
			value = 1.0;
		else
			value = 1.0;
	}
	else
		value = 0.0;
}

void BilinearCoeffs(int n_points, double *x, double *y,
					double **parameters, double **coeffs)
{
	static double eps = 1 / TDatabase::ParamDB->PE_NR;

	int i;
	double *coeff;

	for (i = 0; i < n_points; i++)
	{
		coeff = coeffs[i];
		// double *param = parameters[i];

		coeff[0] = eps;
		coeff[1] = 0;
		coeff[2] = 0;
		coeff[3] = 0;

		coeff[4] = 0;
	}
}

// COmmented out by thivin, due to the external library issue on ubuntu 20.04
// Enable it only when you want to use tetgen for meshing

// // Generate the mesh using triangle.h
void TriaReMeshGen(TDomain *&Domain)
{
	//   int j, ID, k, N_G, *PartMarker, *PointNeighb, maxEpV=0;
	//   int a, b, len1, len2, Neighb_tmp, BDpart;
	//   int i, temp, N_Cells, N_RootCells, CurrVertex, N_Joints, N_Vertices;
	//   int  N_Verti, N_Hori_Top, N_Hori_Bottom,  N_BDVertices;
	//   int CurrComp, In_Index, *Triangles, Neib[2], CurrNeib;
	//   double left, right, top, bottom, N_Points;
	//   double deviation, hi, x0, y0, x, y, phi1, phi2;
	//   double T_a, T_b, C_x, C_y, s, theta;
	//   double dt, area = TDatabase::ParamDB->Area;
	//   double *Coordinates, *Hole_List;

	//   double Xi[4] = {0., 1., 1., 0.};
	//   double Yi[4] = {0., 0., 1., 1.};

	//   TBaseCell **CellTree, *cell;
	//   TBoundPart *BoundPart;
	//   TJoint *Joint;
	//   TCollection *coll;
	//   TVertex **VertexDel, **NewVertices;
	//   TBdLine *UpdateBound[4];

	//   boolean AllowEdgeRef = (boolean) TDatabase::ParamDB->MESHGEN_ALLOW_EDGE_REF;

	//   struct triangulateio In, Out;
	//   std::ostringstream opts;
	//   opts << " ";

	//   Out.pointlist = NULL;
	//   Out.pointattributelist = NULL;
	//   Out.pointmarkerlist = NULL;
	//   Out.trianglelist = NULL;
	//   Out.triangleattributelist = NULL;
	//   Out.trianglearealist = NULL;
	//   Out.neighborlist = NULL;
	//   Out.segmentlist = NULL;
	//   Out.segmentmarkerlist = NULL;
	//   Out.holelist = NULL;
	//   Out.regionlist = NULL;
	//   Out.edgelist = NULL;
	//   Out.edgemarkerlist = NULL;
	//   Out.normlist = NULL;

	//   opts.seekp(std::ios::beg);

	//   BoundPart = Domain->GetBdPart(0);
	//   UpdateBound[0]  = (TBdLine*)BoundPart->GetBdComp(0);
	//   UpdateBound[1]  = (TBdLine*)BoundPart->GetBdComp(1);
	//   UpdateBound[2]  = (TBdLine*)BoundPart->GetBdComp(2);
	//   UpdateBound[3]  = (TBdLine*)BoundPart->GetBdComp(3);

	// //OutPut("MESHGEN_REF_QUALIT " << TDatabase::ParamDB->MESHGEN_REF_QUALITY << endl);

	//   opts<<'p'; // Constrained Delaunay Triangulation:
	//            // initial values - only points defined on the boundary of the domain;
	//            // triangulation near boundary may variate from Delaunay criterion
	//   opts<<"q"<<  TDatabase::ParamDB->MESHGEN_REF_QUALITY;
	//               // Quality mesh generation with no angles smaller than 20 degrees;
	//   opts<<"a"<< area; // Imposes a maximum triangle area.
	//   opts<<'e'; // Outputs a list of edges of the triangulation
	//   opts<<'z'; // Numbers if items starting from 0
	//   //opts<<"VVVV"; // Gives detailed information about what Triangle is doing
	//   opts<<'Q'; // Supress all explanation of what Triangle is doing, unless an error occurs
	// //   opts<<'Y'; // Supress adding vertices on boundary edges
	//   opts<<ends;

	//    N_Points = int (TDatabase::ParamDB->P6);
	//   N_Hori_Top  = N_Points;      // number of horrizontal BD vertices
	//   N_Hori_Bottom  = N_Points;
	//   N_Verti = N_Points;       // number of vertical BD vertices

	//   N_BDVertices = N_Hori_Top+ N_Hori_Bottom + 2*N_Verti;
	//   In.numberofpoints = N_BDVertices;
	//   In.pointlist = new double[2*In.numberofpoints];
	//   In.pointmarkerlist = new int[In.numberofpoints];
	//   In.numberofpointattributes = 0;

	//   In.numberofsegments = In.numberofpoints;
	//   In.segmentlist = new int[2*In.numberofsegments];
	//   In.segmentmarkerlist = new int[In.numberofsegments];
	//   In.numberofregions = 0;
	//   In.regionlist = NULL;
	//   In.numberofholes = 0;
	//   In.holelist = NULL;

	//   In_Index = 0;
	//   CurrComp = 1;

	//   hi = (Xi[1] - Xi[0])/(double)N_Hori_Bottom;
	//   x0 = Xi[0];
	//   y0 = Yi[0];
	//   x  = Xi[0];

	//   // points and segments on the horizontal boundary bottom (marker=1)
	//   for(i=0;i<N_Hori_Bottom;i++) // without last point
	//    {
	//     x = x0 + (double)i*hi;
	//     In.pointlist[2*In_Index] = x;
	//     In.pointlist[2*In_Index+1] = y0;
	// //      cout<<" x : "<< In.pointlist[2*In_Index] << " y : "<< In.pointlist[2*In_Index+1] <<endl;
	//     In.pointmarkerlist[In_Index] = CurrComp;
	//     In.segmentlist[2*In_Index] = In_Index;
	//     In.segmentlist[2*In_Index+1] = In_Index+1;
	//     In.segmentmarkerlist[In_Index] = CurrComp;
	//     In_Index++;
	//    }
	//   CurrComp++;

	//   hi = (Yi[2] - Yi[1])/(double)N_Verti;
	//   x0 = Xi[1];
	//   y0 = Yi[1];
	//   y  = Yi[1];

	//   for(i=0;i<N_Verti;i++) // without last point
	//    {
	//     y = y0 + (double)i*hi;
	//     In.pointlist[2*In_Index] = x0;
	//     In.pointlist[2*In_Index+1] = y;
	// //      cout<<" x : "<< In.pointlist[2*In_Index] << " y : "<< In.pointlist[2*In_Index+1] <<endl;
	//     In.pointmarkerlist[In_Index] = CurrComp;
	//     In.segmentlist[2*In_Index] = In_Index;
	//     In.segmentlist[2*In_Index+1] = In_Index+1;
	//     In.segmentmarkerlist[In_Index] = CurrComp;
	//     In_Index++;

	//    }
	//   CurrComp++;

	//   hi = (Xi[3] - Xi[2])/(double)N_Hori_Top;
	//   x0 = Xi[2];
	//   y0 = Yi[2];
	//   x  = Xi[2];
	//   // points and segments on the horizontal boundary (marker=1)
	//  for(i=0;i<N_Hori_Top;i++) // without last point
	//    {
	//     x = x0 + (double)i*hi;
	//     In.pointlist[2*In_Index] = x;
	//     In.pointlist[2*In_Index+1] = y0;
	// //      cout<<" x : "<< In.pointlist[2*In_Index] << " y : "<< In.pointlist[2*In_Index+1] <<endl;
	//     In.pointmarkerlist[In_Index] = CurrComp;
	//     In.segmentlist[2*In_Index] = In_Index;
	//     In.segmentlist[2*In_Index+1] = In_Index+1;
	//     In.segmentmarkerlist[In_Index] = CurrComp;
	//     In_Index++;

	//    }
	//   CurrComp++;

	//   hi = (Yi[0] - Yi[3])/(double)N_Verti;
	//   x0 = Xi[3];
	//   y0 = Yi[3];
	//   y  = Yi[3];

	//  for(i=0;i<N_Verti;i++) // without last point
	//    {
	//     y = y0 + (double)i*hi;
	//     In.pointlist[2*In_Index] = x0;
	//     In.pointlist[2*In_Index+1] = y;
	// //      cout<<" x : "<< In.pointlist[2*In_Index] << " y : "<< In.pointlist[2*In_Index+1] <<endl;
	//     In.pointmarkerlist[In_Index] = CurrComp;
	//     In.segmentlist[2*In_Index] = In_Index;
	//     In.segmentlist[2*In_Index+1] = In_Index+1;
	//     In.segmentmarkerlist[In_Index] = CurrComp;
	//     In_Index++;

	//    }
	//   CurrComp++;

	//   In.segmentlist[2*(In_Index-1)+1] = 0;

	//   if(Out.pointlist!=NULL) {
	//     free(Out.pointlist); Out.pointlist = NULL;}
	//   if(Out.pointattributelist!=NULL) {
	//     free(Out.pointattributelist); Out.pointattributelist = NULL;}
	//   if(Out.pointmarkerlist!=NULL) {
	//     free(Out.pointmarkerlist); Out.pointmarkerlist = NULL;}
	//   if(Out.trianglelist!=NULL) {
	//     free(Out.trianglelist); Out.trianglelist = NULL;}
	//   if(Out.triangleattributelist!=NULL) {
	//     free(Out.triangleattributelist); Out.triangleattributelist = NULL;}
	//   if(Out.trianglearealist!=NULL) {
	//     free(Out.trianglearealist); Out.trianglearealist = NULL;}
	//   if(Out.neighborlist!=NULL) {
	//     free(Out.neighborlist); Out.neighborlist = NULL;}
	//   if(Out.segmentlist!=NULL) {
	//     free(Out.segmentlist); Out.segmentlist = NULL;}
	//   if(Out.segmentmarkerlist!=NULL) {
	//     free(Out.segmentmarkerlist); Out.segmentmarkerlist = NULL;}
	//   if(Out.holelist!=NULL) {
	//     free(Out.holelist); Out.holelist = NULL;}
	//   if(Out.regionlist!=NULL) {
	//     free(Out.regionlist); Out.regionlist = NULL;}
	//   if(Out.edgelist!=NULL) {
	//     free(Out.edgelist); Out.edgelist = NULL;}
	//   if(Out.edgemarkerlist!=NULL) {
	//     free(Out.edgemarkerlist); Out.edgemarkerlist = NULL;}
	//   if(Out.normlist!=NULL) {
	//     free(Out.normlist); Out.normlist = NULL;}

	//   // call triangle
	//   triangulate((char*)opts.str().c_str(), &In, &Out, (struct triangulateio *)NULL);

	//   Domain->GetTreeInfo(CellTree, N_RootCells);
	//   coll = Domain->GetCollection(It_Finest, 0);
	//   N_Cells = coll->GetN_Cells();

	// //   cout<<N_Cells<<"\n";
	// //   exit(0);

	//   // remove all existing vertices and joints
	//   VertexDel = new TVertex*[3*N_RootCells];
	//   // DelCell = new TGridCell*[N_Cells];

	//   CurrVertex = 0;
	//   for(i=0;i<N_Cells;i++)
	//     {
	//       cell = coll->GetCell(i);
	//       N_Joints = cell->GetN_Joints();
	//       N_Vertices = cell->GetN_Vertices();
	//    for(j=0;j<N_Joints;j++)
	//         {
	//          if(CurrVertex==0)
	//           {
	//               VertexDel[CurrVertex] = cell->GetVertex(j);
	//               CurrVertex++;
	//            }
	//          else
	//           {
	//            ID = 0;
	//            for(k=0;k<CurrVertex;k++)
	//            if(VertexDel[k]==cell->GetVertex(j))
	//             {
	//              ID = 1; break;
	//             }
	//            if(ID!=1)
	//             {
	//              VertexDel[CurrVertex] = cell->GetVertex(j);
	//              CurrVertex++;
	//             }
	//            } // else if(CurrVertex==0)
	//            ID = 0;
	//           for(k=0;k<CurrVertex;k++)
	//           if(VertexDel[k]==cell->GetVertex((j+1)%N_Vertices))
	//            {
	//             ID = 1; break;
	//            }
	//             if(ID!=1)
	//            {
	//             VertexDel[CurrVertex] = cell->GetVertex((j+1)%N_Vertices);
	//             CurrVertex++;
	//            }
	//         } // for j
	//     } // for i
	//    cout<<CurrVertex<<" "<<N_RootCells<<"\n";

	//    for(i=0;i<CurrVertex;i++)
	//    delete VertexDel[i];

	//    delete []VertexDel;
	//    OutPut(CurrVertex<<" vertices were deleted"<<endl);

	// // remove all existing cells and joints
	//     for(i=0;i<N_RootCells;i++)
	//     delete (TGridCell*)CellTree[i];
	//     OutPut(N_RootCells<<" cells were deleted"<<endl);
	//     delete CellTree;
	//     delete coll;

	//     N_RootCells = Out.numberoftriangles;
	//   // allocate auxillary fields
	//   Coordinates = Out.pointlist;
	//   Triangles = Out.trianglelist;
	//   PartMarker = new int[Out.numberofpoints];
	// // generate new vertices
	//   N_G = Out.numberofpoints;
	//   NewVertices = new TVertex*[N_G];

	//   for (i=0;i<N_G;i++)
	//      NewVertices[i] = new TVertex(Coordinates[2*i], Coordinates[2*i+1]);

	//       // set bounding box
	//   left = 0.0;
	//   bottom = 0.0;
	//   right = 1.0;
	//   top = 1.0;
	//  for(i=0;i<In.numberofpoints;i++)
	//     {
	//       if(left>In.pointlist[2*i]) left = In.pointlist[2*i];
	//       if(right<In.pointlist[2*i]) right = In.pointlist[2*i];
	//       if(top<In.pointlist[2*i+1]) top = In.pointlist[2*i+1];
	//       if(bottom>In.pointlist[2*i+1]) bottom = In.pointlist[2*i+1];
	//     }

	// //  OutPut("left: "<<left<<" right: "<<right<<" top: "<<top<<" bottom: "<<bottom<<endl);

	//   Domain->SetBoundBox(right-left,top-bottom);
	//   Domain->SetBoundBoxstart(left,bottom);

	//   cout << "N_RootCells :" << N_RootCells << endl;

	//  // generate cells
	//    CellTree = new TBaseCell*[N_RootCells];

	//   for (i=0;i<N_RootCells;i++)
	//   {
	//     CellTree[i] = new TMacroCell(TDatabase::RefDescDB[Triangle], 0);

	//     CellTree[i]->SetVertex(0, NewVertices[Out.trianglelist[3*i    ]]);
	//     CellTree[i]->SetVertex(1, NewVertices[Out.trianglelist[3*i + 1]]);
	//     CellTree[i]->SetVertex(2, NewVertices[Out.trianglelist[3*i + 2]]);

	//       ((TMacroCell *) CellTree[i])->SetSubGridID(0);
	//   }
	//  Domain->SetTreeInfo(CellTree, N_RootCells);

	//   // initialize iterators
	//   TDatabase::IteratorDB[It_EQ]->SetParam(Domain);
	//   TDatabase::IteratorDB[It_LE]->SetParam(Domain);
	//   TDatabase::IteratorDB[It_Finest]->SetParam(Domain);
	//   TDatabase::IteratorDB[It_Between]->SetParam(Domain);
	//   TDatabase::IteratorDB[It_OCAF]->SetParam(Domain);
	// // search neighbours
	//   N_G = Out.numberofpoints;
	//   PointNeighb = new int[N_G];

	//   memset(PointNeighb, 0, N_G *SizeOfInt);
	//   for (i=0;i<3*N_RootCells;i++)
	//     PointNeighb[Triangles[i]]++;

	//   for (i=0;i<N_G;i++)
	//     if (PointNeighb[i] > maxEpV) maxEpV = PointNeighb[i];

	//   delete [] PointNeighb;

	//   PointNeighb = new int[++maxEpV * N_G];

	//   memset(PointNeighb, 0, maxEpV * N_G *SizeOfInt);

	//    // first colomn contains the number of following elements
	//    // for every point at first column we set the number of neighbour points
	//    // at further columns we set the index of corresponding cells
	//   for(i=0;i<3*N_RootCells;i++)
	//    {
	//     j = Triangles[i]*maxEpV;
	//     PointNeighb[j]++;
	//     PointNeighb[j + PointNeighb[j]] = i / 3;
	//    }

	//  // generate new edges
	//   N_G = Out.numberofedges;
	//   for (i=0;i<N_G;i++)
	//   {
	//     a = Out.edgelist[2*i];
	//     b = Out.edgelist[2*i+1];
	//     Neib[0] = -1;
	//     Neib[1] = -1;
	//     CurrNeib = 0;

	//     len1 = PointNeighb[a*maxEpV];
	//     len2 = PointNeighb[b*maxEpV];
	// // find indexes of cells containing the current edge
	//    for (j=1;j<=len1;j++)
	//     {
	//       Neighb_tmp = PointNeighb[a*maxEpV + j];
	//        for (k=1;k<=len2;k++)
	//         if (Neighb_tmp == PointNeighb[b*maxEpV + k])
	//         {
	//           Neib[CurrNeib++] = Neighb_tmp;
	//           break;
	//         }
	//       if (CurrNeib == 2) break;
	//     }

	// if (Out.edgemarkerlist[i]) // 0 for inner edges and Boundcomp+1 for Boundedge respect
	//     {
	//       CurrComp = Out.edgemarkerlist[i] - 1;
	//       if (CurrComp >= 100000) CurrComp -= 100000;

	//       if(Domain->GetBdPart(0)->GetBdComp(CurrComp)->GetTofXY(
	//             NewVertices[a]->GetX(), NewVertices[a]->GetY(), T_a) ||
	//           Domain->GetBdPart(0)->GetBdComp(CurrComp)->GetTofXY(
	//             NewVertices[b]->GetX(), NewVertices[b]->GetY(), T_b))
	//        {
	//           cerr<<"Error: could not set parameter values"<<endl;
	//           OutPut(NewVertices[a]<<endl);
	//           OutPut(NewVertices[b]<<endl);
	//           cout << " CurrComp " << CurrComp <<endl;
	//         //  exit(0);
	//        }

	//       if (CurrNeib == 2)    // 2 cells contain the current edge
	//         if(Domain->GetBdPart(0)->GetBdComp(CurrComp)->IsFreeBoundary())
	//           Joint = new TIsoInterfaceJoint(Domain->GetBdPart(0)->GetBdComp(CurrComp), T_a, T_b,
	//                                          CellTree[Neib[0]], CellTree[Neib[1]]);
	//         else
	//           Joint = new TInterfaceJoint(Domain->GetBdPart(0)->GetBdComp(CurrComp),
	//                   T_a, T_b, CellTree[Neib[0]], CellTree[Neib[1]]);
	//       else
	//         if(Domain->GetBdPart(0)->GetBdComp(CurrComp)->IsFreeBoundary())
	//           Joint = new TIsoBoundEdge(Domain->GetBdPart(0)->GetBdComp(CurrComp), T_a, T_b);
	//         else
	//           Joint = new TBoundEdge(Domain->GetBdPart(0)->GetBdComp(CurrComp), T_a, T_b);
	//     }
	//    else // inner edge
	//     {
	//     if (CurrNeib != 2)
	//         cerr << "Error!!!!!!!! not enough neighbours!" << endl;

	//     Joint = new TJointEqN(CellTree[Neib[0]], CellTree[Neib[1]]);
	//     }
	//  // find the local index for the point 'a' on the cell
	//     for (j=0;j<3;j++)
	//       if (Triangles[3*Neib[0]+j] == a) break;

	//     // find the local index for the point 'b' on the cell
	//     for (k=0;k<3;k++)
	//       if (Triangles[3*Neib[0]+k] == b) break;
	//    k = k*10 + j;

	//     switch (k)
	//     {
	//       case  1:
	//       case 10:
	//         j = 0;
	//         break;
	//       case 12:
	//       case 21:
	//         j = 1;
	//         break;
	//       case  2:
	//       case 20:
	//         j = 2;
	//         break;
	//     }
	//    CellTree[Neib[0]]->SetJoint(j, Joint);

	//    if (Neib[1] != -1)
	//     {
	//       // find the local index for the point 'a' on the cell
	//       for (j=0;j<3;j++)
	//         if (Triangles[3*Neib[1]+j] == a) break;

	//       // find the local index for the point 'b' on the cell
	//       for (k=0;k<3;k++)
	//         if (Triangles[3*Neib[1]+k] == b) break;

	//       k = k*10 + j;
	//     switch (k) // j will contain the local index for the current
	//       {
	//         case  1:
	//         case 10:
	//           j = 0;
	//           break;
	//         case 12:
	//         case 21:
	//           j = 1;
	//           break;
	//         case  2:
	//         case 20:
	//           j = 2;
	//           break;
	//       }
	// CellTree[Neib[1]]->SetJoint(j, Joint);
	//     }

	//   if (Joint->GetType() == InterfaceJoint ||
	//         Joint->GetType() == IsoInterfaceJoint)
	//       ((TInterfaceJoint *) Joint)->CheckOrientation();
	//   }

	//   delete [] NewVertices;
	//   delete [] PointNeighb;
	//   delete [] In.pointlist;
	//   delete [] In.pointmarkerlist;
	//   delete [] In.segmentlist;
	//   delete [] In.segmentmarkerlist;
	//   if(Out.pointlist!=NULL) {
	//     free(Out.pointlist); Out.pointlist = NULL;}
	//   if(Out.pointattributelist!=NULL) {
	//     free(Out.pointattributelist); Out.pointattributelist = NULL;}
	//   if(Out.pointmarkerlist!=NULL) {
	//     free(Out.pointmarkerlist); Out.pointmarkerlist = NULL;}
	//   if(Out.trianglelist!=NULL) {
	//     free(Out.trianglelist); Out.trianglelist = NULL;}
	//   if(Out.triangleattributelist!=NULL) {
	//     free(Out.triangleattributelist); Out.triangleattributelist = NULL;}
	//   if(Out.trianglearealist!=NULL) {
	//     free(Out.trianglearealist); Out.trianglearealist = NULL;}
	//   if(Out.neighborlist!=NULL) {
	//     free(Out.neighborlist); Out.neighborlist = NULL;}
	//   if(Out.segmentlist!=NULL) {
	//     free(Out.segmentlist); Out.segmentlist = NULL;}
	//   if(Out.segmentmarkerlist!=NULL) {
	//     free(Out.segmentmarkerlist); Out.segmentmarkerlist = NULL;}
	//   if(Out.holelist!=NULL) {
	//     free(Out.holelist); Out.holelist = NULL;}
	//   if(Out.regionlist!=NULL) {
	//     free(Out.regionlist); Out.regionlist = NULL;}
	//   if(Out.edgelist!=NULL) {
	//     free(Out.edgelist); Out.edgelist = NULL;}
	//   if(Out.edgemarkerlist!=NULL) {
	//     free(Out.edgemarkerlist); Out.edgemarkerlist = NULL;}
	//   if(Out.normlist!=NULL) {
	//     free(Out.normlist); Out.normlist = NULL;}

	// //======================================================================
	// // Triangular for grid generation --end
	// //======================================================================

	// //   cout<< "tetgen" <<endl;
	// //   exit(0);
	// //

} // TriaReMeshGen

// Function to compute L2 Error against the Actual Solution
double ComputeL2ErrorDifference(TFESpace2D *fespace, TFEFunction2D *FEM_FEFunt, TFEFunction2D *Pinns_FEFunt)
{
	// Obtain Cell Data
	TCollection *coll = fespace->GetCollection();
	int N_Cells = coll->GetN_Cells();

	double *FEM_Solution = FEM_FEFunt->GetValues();
	double *PINNS_Solution = Pinns_FEFunt->GetValues();

	// Begin Index array for each cell ( the array has the starting index value for that cell in the globalDOF to local DOF mapping array )
	int *BeginIndex = fespace->GetBeginIndex();
	int *GlobalNumbers = fespace->GetGlobalNumbers();

	// --- Quadrature Formula Arrays  ------------------//
	int N_Points2;
	double *Weights2, *t1, *t2; // Weights - Quadrature Weights array ; t1  -- Quadrature point ( xi ) in ref coordinate ; t2 -  Quadrature Point ( eta ) in Ref Coordinate
	bool Needs2ndDer[1];
	Needs2ndDer[0] = FALSE;
	double AbsDetjk[MaxN_QuadPoints_2D];
	double X[MaxN_QuadPoints_2D];
	double Y[MaxN_QuadPoints_2D];

	// FE Values Arrays
	double **origvaluesD00; // Shape function values at quadrature Points
	double **origvaluesD10; // Shape Function Derivatives ( x ) at Quadrature Points
	double **origvaluesD01; // Shape Function Derivatives ( y ) at Quadrature Points

	double norm = 0;

	for (int cellNr = 0; cellNr < N_Cells; cellNr++)
	{
		// Get the Cell object from the Cells Collection based on cell id
		TBaseCell *cell = coll->GetCell(cellNr);
		// Get the "ID" of Finite Element for the given 2D Element ( Conforming/NonConforming-Order Finite Element : eg : it could be Conforming-2nd order Finite Element )
		FE2D FEId = fespace->GetFE2D(cellNr, cell);
		// Get the Class object for that 2d FEM Element , which has all the details like Shape functions , Nodal point locations for that location, Reference Transformation ( Affine , Bilinear )
		TFE2D *Element = TFEDatabase2D::GetFE2D(FEId);
		// Class for basis functions in 2D ( Number of basis functions ), basis function values and Derivatives
		TBaseFunct2D *bf = Element->GetBaseFunct2D();
		// Get the Reference Elemet
		BF2DRefElements RefElement = TFEDatabase2D::GetRefElementFromFE2D(FEId);
		// Get the reference Transformation -- Affine Mapping / Bilnea Mapping of Triangle or Quadrilateral
		RefTrans2D referenceTransformation = TFEDatabase2D::GetRefTrans2D_IDFromFE2D(FEId);

		// Get the number of basis functions in the Current Cell ( Number of Local DOF)
		int N_BaseFunct = Element->GetN_DOF();
		// Type of Basis Function in 2D
		BaseFunct2D BaseFunct_ID = Element->GetBaseFunct2D_ID();

		// Get the Area ( Measure of Cell )
		double area = cell->GetMeasure();

		switch (referenceTransformation)
		{
		case QuadBilinear:
		{
			int l = bf->GetPolynomialDegree();									   // Get the Polynomial Degreee  of the basis functions
			QuadFormula2D QF2 = TFEDatabase2D::GetQFQuadFromDegree(2 * l);		   // Get te ID of Quadrature Formula
			TQuadFormula2D *QuadratureRule = TFEDatabase2D::GetQuadFormula2D(QF2); // Get the Quadrature Rule Objetc based on Quadrature ID
			QuadratureRule->GetFormulaData(N_Points2, Weights2, t1, t2);		   // get the Quadrature points , Weights

			// Set the values on the Reference Cell
			TRefTrans2D *F_K = TFEDatabase2D::GetRefTrans2D(QuadBilinear);
			TFEDatabase2D::SetCellForRefTrans(cell, QuadBilinear); // Set the Cell for Current reference Transformation

			// Get Original Coordinates from reference Coordinates and the Determinant of jacobian
			TFEDatabase2D::GetOrigFromRef(QuadBilinear, N_Points2, t1, t2, X, Y, AbsDetjk); // Get the Original Co-orinates for the cell from xi values

			// Get all the original Values from the Referece cell values.
			TFEDatabase2D::GetOrigValues(QuadBilinear, 1, &BaseFunct_ID, N_Points2, t1, t2, QF2, Needs2ndDer);

			// The below are 2D arrays in the form
			// Values[QuadraturePointLocation][ShapeFunction]  i.e, the Value of Shapefunction at all quadrature points for each shape functions
			origvaluesD00 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D00); // Shape Function Values at Quadrature Points
			origvaluesD10 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D10); // Shape Function Values at Quadrature Points
			origvaluesD01 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D01); // Shape Function Values at Quadrature Point

			break;
		}

		case QuadAffin:
		{
			int l = bf->GetPolynomialDegree();									   // Get the Polynomial Degreee  of the basis functions
			QuadFormula2D QF2 = TFEDatabase2D::GetQFQuadFromDegree(2 * l);		   // Get te ID of Quadrature Formula
			TQuadFormula2D *QuadratureRule = TFEDatabase2D::GetQuadFormula2D(QF2); // Get the Quadrature Rule Objetc based on Quadrature ID
			QuadratureRule->GetFormulaData(N_Points2, Weights2, t1, t2);		   // get the Quadrature points , Weights

			// Set the values on the Reference Cell
			TRefTrans2D *F_K = TFEDatabase2D::GetRefTrans2D(QuadAffin);

			TFEDatabase2D::SetCellForRefTrans(cell, QuadAffin); // Set the Cell for Current reference Transformation

			// Get Original Coordinates from reference Coordinates and the Determinant of jacobian
			TFEDatabase2D::GetOrigFromRef(QuadAffin, N_Points2, t1, t2, X, Y, AbsDetjk); // Get the Original Co-orinates for the cell from xi values

			// Get all the original Values from the Referece cell values.
			TFEDatabase2D::GetOrigValues(QuadAffin, 1, &BaseFunct_ID, N_Points2, t1, t2, QF2, Needs2ndDer);

			// The below are 2D arrays in the form
			// Values[QuadraturePointLocation][ShapeFunction]  i.e, the Value of Shapefunction at all quadrature points for each shape functions
			origvaluesD00 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D00); // Shape Function Values at Quadrature Points
			origvaluesD10 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D10); // Shape Function Values at Quadrature Points
			origvaluesD01 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D01); // Shape Function Values at Quadrature Point

			break;
		}

		case TriaAffin:
		{
			FE2D UsedElements[1];
			FE2D FEid = fespace->GetFE2D(cellNr, cell);
			UsedElements[0] = FEid;
			bool SecondDer[1] = {FALSE};

			TFEDatabase2D::GetOrig(1, UsedElements,
								   coll, cell, SecondDer,
								   N_Points2, t1, t2, Weights2, X, Y, AbsDetjk);

			// The below are 2D arrays in the form
			// Values[QuadraturePointLocation][ShapeFunction]  i.e, the Value of Shapefunction at all quadrature points for each shape functions
			origvaluesD00 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D00); // Shape Function Values at Quadrature Points
			origvaluesD10 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D10); // Shape Function Values at Quadrature Points
			origvaluesD01 = TFEDatabase2D::GetOrigElementValues(BaseFunct_ID, D01); // Shape Function Values at Quadrature Point

			break;
		}

		default:
		{
			cout << " Unknown Reftype " << endl;
			cout << " REF TYPE : " << referenceTransformation << endl;
			exit(0);
			break;
		}
		}

		// Get the Local to Global DOF Mapping for the Current Cell
		// DOF[1] contains the global DOF number of the local DOF number in the cell.
		int *DOF = GlobalNumbers + BeginIndex[cellNr];

		// Begin Quadrature Integration
		for (int quadPt = 0; quadPt < N_Points2; quadPt++)
		{
			double Mult = Weights2[quadPt] * AbsDetjk[quadPt];
			double *orgD00 = origvaluesD00[quadPt];

			double actual = 0;
			double computed = 0;
			for (int j = 0; j < N_BaseFunct; j++)
			{
				int GlobalDOF = DOF[j];

				// norm += Mult*(FEM_Solution[GlobalDOF]*orgD00[j]*FEM_Solution[GlobalDOF]*orgD00[j]);
				// Norm -- Find L2 Norm
				actual += FEM_Solution[GlobalDOF] * orgD00[j];
				computed += PINNS_Solution[GlobalDOF] * orgD00[j];
			}

			double error = actual - computed;

			norm += error * error * Mult;
			// cout << " Print Norm : " << norm  << "  " << actual << "  " << computed <<endl;
		}
	}
	// return norm;
	return sqrt(norm);
}

std::vector<int> GenerateMapping(std::string filename, TFEVectFunct2D *co_ordinates)
{

	double *xVal = co_ordinates->GetComponent(0)->GetValues();
	double *yVal = co_ordinates->GetComponent(1)->GetValues();

	int numPoints = co_ordinates->GetLength();

	// Declare arrays for storing the read arrays
	std::vector<double> xVTK(numPoints, 0);
	std::vector<double> yVTK(numPoints, 0);

	// Declare the Array to Store Mapping values
	std::vector<int> mappingValues(numPoints, 0);

	cout << filename << endl;
	// Extract the data available in VTK file
	std::ifstream file;
	file.open(filename);

	if (file.fail() || !file.is_open() || file.bad())
	{
		cout << " Error Openning the File " << endl;
		exit(0);
	}

	std::istringstream buffer;
	std::string lineData;

	// Read Every line
	int count = 0;
	while (std::getline(file, lineData))
	{
		std::setprecision(10);
		std::istringstream iss(lineData);

		std::string s;
		std::getline(iss, s, ',');
		std::istringstream(s) >> std::setprecision(10) >> xVTK[count];

		std::getline(iss, s, ',');
		std::istringstream(s) >> std::setprecision(10) >> yVTK[count];

		count++;
	}

	file.close();

	if (numPoints == count)
	{
		cout << "Number of Data points Read : " << count << endl;
	}
	else
	{
		cout << " Mismatch between the number of datapoints read and the given co-ordinates" << endl;
		cout << " Points from file : " << count << " N_DOF : " << numPoints << endl;
		exit(0);
	}

	// Code to identify the Mapping value
	// loop through all the numbers and find which matches tha pair more.

	double eps = 1e-5;
	int matchFound = 0;
	bool matched = false;
	for (int i = 0; i < numPoints; i++)
	{
		double actualX = xVTK[i];
		double actualY = yVTK[i];
		for (int j = 0; j < numPoints; j++)
		{
			if (fabs(xVal[j] - actualX) < eps && fabs(yVal[j] - actualY) < eps)
			{
				// Match Found
				mappingValues[i] = j;
				matchFound++;
				matched = true;
				break;
			}
		}

		if (!matched)
			cout << " No match Found : " << actualX << " " << actualY << endl;

		matched = false;
	}

	if (matchFound != numPoints)
	{
		cout << " Matched : " << matchFound << " total : " << numPoints << endl;
		cout << " Mapping could not be obtained for " << numPoints - matchFound << " points" << endl;
	}

	// return the Mapping Array
	return mappingValues;
}

// Function to read the Data, perform mapping and then Set the values in the Vect Function
void readPinnsData(TFEFunction2D *PinnsFeFunction, std::vector<int> mapping, const char *filename)
{

	double *PinnsSolution = PinnsFeFunction->GetValues();
	int N_DOF = PinnsFeFunction->GetLength();

	// Read the file
	std::ifstream file;
	file.open(filename);

	if (!file)
	{
		cout << " Error in Reading Files for PINNS data : Filename :  " << filename << endl;
		exit(0);
	}

	int numLines = 0;
	std::string lineData;
	double val = 0.0;
	while (std::getline(file, lineData))
	{

		std::istringstream iss(lineData);
		iss >> val;
		PinnsSolution[mapping[numLines]] = val;
		numLines++;
	}

	file.close();

	if (numLines != N_DOF)
	{
		printf("The N_DOF %d , does not matches with the numLines read %d \n", N_DOF, numLines);
	}
}