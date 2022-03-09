/********************************************************
 * Kernels to be optimized for the Metu Ceng Performance Lab
 ********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "defs.h"

/*
 * Please fill in the following team struct
 */
team_t team = {
    "erdeniz",                     /* Team name */

    "Mehmet Erdeniz Aydoğdu",             /* First member full name */
    "e2380103",                 /* First member id */

    "",                         /* Second member full name (leave blank if none) */
    "",                         /* Second member id (leave blank if none) */

    "",                         /* Third member full name (leave blank if none) */
    ""                          /* Third member id (leave blank if none) */
};

/****************
 * EXPOSURE FUSION KERNEL *
 ****************/

/*******************************************************
 * Your different versions of the exposure fusion kernel go here
 *******************************************************/

/*
 * naive_fusion - The naive baseline version of exposure fusion
 */
char naive_fusion_descr[] = "naive_fusion: Naive baseline exposure fusion";
void naive_fusion(int dim, int *img, int *w, int *dst) {

    int i, j, k;
    for(k = 0; k < 4; k++){
        for(i = 0; i < dim; i++) {
            for(j = 0; j < dim; j++) {
                   dst[i*dim+j] += w[k*dim*dim+i*dim+j] * img[k*dim*dim+i*dim+j];
            }
        }
    }
}

/*
 * fusion - Your current working version of fusion
 * IMPORTANT: This is the version you will be graded on
 */
char fusion_descr[] = "fusion: Current working version";
void fusion(int dim, int *img, int *w, int *dst)
{
    int i, j, d, r,r2,r3,r4,r5,r6,r7,r8, r9, r10, r11, r12, r13, r14, r15, r16;
    int r17, r18, r19, r20, r21, r22, r23, r24, r25, r26, r27, r28, r29, r30, r31, r32;
    int *im2, *we2, *im, *we, *ds; 
    d = dim * dim;
        for(i = 0; i < dim; i++) {
	    im = img;
	    we = w;
	    ds = dst;
            for(j = 0; j < dim; j+= 32) {
		   im2 = im;
		   we2 = we;
		   r = we2[0] * im2[0];
		   r2 = we2[1] * im2[1]; 
		   r3 = we2[2] * im2[2]; 
		   r4 = we2[3] * im2[3]; 
		   r5 = we2[4] * im2[4]; 
		   r6 = we2[5] * im2[5]; 
		   r7 = we2[6] * im2[6]; 
		   r8 = we2[7] * im2[7];
		   r9 = we2[8] * im2[8];
                   r10 = we2[9] * im2[9];
                   r11 = we2[10] * im2[10];
                   r12 = we2[11] * im2[11];
                   r13 = we2[12] * im2[12];
                   r14 = we2[13] * im2[13];
                   r15 = we2[14] * im2[14];
                   r16 = we2[15] * im2[15];
		   r17 = we2[16] * im2[16];
                   r18 = we2[17] * im2[17];
                   r19 = we2[18] * im2[18];
                   r20 = we2[19] * im2[19];
                   r21 = we2[20] * im2[20];
                   r22 = we2[21] * im2[21];
                   r23 = we2[22] * im2[22];
                   r24 = we2[23] * im2[23];
                   r25 = we2[24] * im2[24];
                   r26 = we2[25] * im2[25];
                   r27 = we2[26] * im2[26];
                   r28 = we2[27] * im2[27];
                   r29 = we2[28] * im2[28];
                   r30 = we2[29] * im2[29];
                   r31 = we2[30] * im2[30];
                   r32 = we2[31] * im2[31];

		   im2 += d;
		   we2 += d;
		   r += (we2[0] * im2[0]);
		   r2 += we2[1] * im2[1]; 
		   r3 += we2[2] * im2[2]; 
		   r4 += we2[3] * im2[3];
		   r5 += we2[4] * im2[4];
                   r6 += we2[5] * im2[5];
                   r7 += we2[6] * im2[6];
                   r8 += we2[7] * im2[7];
		   r9 += we2[8] * im2[8];
                   r10 += we2[9] * im2[9];
                   r11 += we2[10] * im2[10];
                   r12 += we2[11] * im2[11];
                   r13 += we2[12] * im2[12];
                   r14 += we2[13] * im2[13];
                   r15 += we2[14] * im2[14];
                   r16 += we2[15] * im2[15];
		   r17 += we2[16] * im2[16];
                   r18 += we2[17] * im2[17];
                   r19 += we2[18] * im2[18];
                   r20 += we2[19] * im2[19];
                   r21 += we2[20] * im2[20];
                   r22 += we2[21] * im2[21];
                   r23 += we2[22] * im2[22];
                   r24 += we2[23] * im2[23];
                   r25 += we2[24] * im2[24];
                   r26 += we2[25] * im2[25];
                   r27 += we2[26] * im2[26];
                   r28 += we2[27] * im2[27];
                   r29 += we2[28] * im2[28];
                   r30 += we2[29] * im2[29];
                   r31 += we2[30] * im2[30];
                   r32 += we2[31] * im2[31];
 
		   im2 += d;
		   we2 += d;
		   r += (we2[0] * im2[0]);
		   r2 += we2[1] * im2[1]; 
		   r3 += we2[2] * im2[2]; 
		   r4 += we2[3] * im2[3];
		   r5 += we2[4] * im2[4];
                   r6 += we2[5] * im2[5];
                   r7 += we2[6] * im2[6];
                   r8 += we2[7] * im2[7];
		   r9 += we2[8] * im2[8];
                   r10 += we2[9] * im2[9];
                   r11 += we2[10] * im2[10];
                   r12 += we2[11] * im2[11];
                   r13 += we2[12] * im2[12];
                   r14 += we2[13] * im2[13];
                   r15 += we2[14] * im2[14];
                   r16 += we2[15] * im2[15];
		   r17 += we2[16] * im2[16];
                   r18 += we2[17] * im2[17];
                   r19 += we2[18] * im2[18];
                   r20 += we2[19] * im2[19];
                   r21 += we2[20] * im2[20];
                   r22 += we2[21] * im2[21];
                   r23 += we2[22] * im2[22];
                   r24 += we2[23] * im2[23];
                   r25 += we2[24] * im2[24];
                   r26 += we2[25] * im2[25];
                   r27 += we2[26] * im2[26];
                   r28 += we2[27] * im2[27];
                   r29 += we2[28] * im2[28];
                   r30 += we2[29] * im2[29];
                   r31 += we2[30] * im2[30];
                   r32 += we2[31] * im2[31];
 
		   im2 += d;
		   we2 += d; 
		   r += (we2[0] * im2[0]);
		   r2 += we2[1] * im2[1]; 
		   r3 += we2[2] * im2[2]; 
		   r4 += we2[3] * im2[3];
		   r5 += we2[4] * im2[4];
                   r6 += we2[5] * im2[5];
                   r7 += we2[6] * im2[6];
                   r8 += we2[7] * im2[7];
		   r9 += we2[8] * im2[8];
                   r10 += we2[9] * im2[9];
                   r11 += we2[10] * im2[10];
                   r12 += we2[11] * im2[11];
                   r13 += we2[12] * im2[12];
                   r14 += we2[13] * im2[13];
                   r15 += we2[14] * im2[14];
                   r16 += we2[15] * im2[15]; 
		   r17 += we2[16] * im2[16];
                   r18 += we2[17] * im2[17];
                   r19 += we2[18] * im2[18];
                   r20 += we2[19] * im2[19];
                   r21 += we2[20] * im2[20];
                   r22 += we2[21] * im2[21];
                   r23 += we2[22] * im2[22];
                   r24 += we2[23] * im2[23];
                   r25 += we2[24] * im2[24];
                   r26 += we2[25] * im2[25];
                   r27 += we2[26] * im2[26];
                   r28 += we2[27] * im2[27];
                   r29 += we2[28] * im2[28];
                   r30 += we2[29] * im2[29];
                   r31 += we2[30] * im2[30];
                   r32 += we2[31] * im2[31];

		   ds[0] = r;
		   ds[1] = r2;
		   ds[2] = r3;
		   ds[3] = r4;
		   ds[4] = r5;
		   ds[5] = r6;
		   ds[6] = r7;
		   ds[7] = r8;
		   ds[8] = r9;
		   ds[9] = r10;
		   ds[10] = r11;
		   ds[11] = r12;
		   ds[12] = r13;
		   ds[13] = r14;
		   ds[14] = r15;
		   ds[15] = r16;
		   ds[16] = r17;
		   ds[17] = r18;
		   ds[18] = r19;
		   ds[19] = r20;
		   ds[20] = r21;
		   ds[21] = r22;
		   ds[22] = r23;
		   ds[23] = r24;
		   ds[24] = r25;
		   ds[25] = r26;
		   ds[26] = r27;
		   ds[27] = r28;
		   ds[28] = r29;
		   ds[29] = r30;
		   ds[30] = r31;
		   ds[31] = r32;
		   im+=32;
		   we+=32;
		   ds+=32;
            }
	    img += dim;
	    w += dim;
	    dst += dim;
        }
}

/*********************************************************************
 * register_fusion_functions - Register all of your different versions
 *     of the fusion kernel with the driver by calling the
 *     add_fusion_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_fusion_functions()
{
    add_fusion_function(&naive_fusion, naive_fusion_descr);
    add_fusion_function(&fusion, fusion_descr);
    /* ... Register additional test functions here */
}

/***************************
 * GAUSSIAN BLUR KERNEL *
 ***************************/

/******************************************************
 * Your different versions of the Gaussian blur functions go here
 ******************************************************/

/*
 * naive_blur - The naive baseline version of Gussian blur
 */
char naive_blur_descr[] = "naive_blur The naive baseline version of Gaussian blur";
void naive_blur(int dim, float *img, float *flt, float *dst) {

   int i, j, k, l;

    for(i = 0; i < dim-5+1; i++){
        for(j = 0; j < dim-5+1; j++) {
            for(k = 0; k < 5; k++){
                for(l = 0; l < 5; l++) {
                    dst[i*dim+j] = dst[i*dim+j] + img[(i+k)*dim+j+l] * flt[k*dim+l];
                }
            }
        }
    }
}

void blur_2(int dim, float *img, float *flt, float *dst)
{
    int i, j, ind = dim - 4;
    float r;
    float flv[25];
    float *im, *ds, *im2;

    for(i = 0; i < 25; i+=5){
            flv[i] = flt[0];
            flv[i+1] = flt[1];
            flv[i+2] = flt[2];
            flv[i+3] = flt[3];
            flv[i+4] = flt[4];
	flt += dim;
    }

    for(i = 0; i < ind; i++){
        im = img;
        ds = dst;
        for(j = 0; j < ind; j++){
            im2 = im;
            r = im2[0] * flv[0];
            r += (im2[1] * flv[1]) + (im2[2] * flv[2]) + (im2[3] * flv[3]) + (im2[4] * flv[4]);
            im2 += dim;
	    r += (im2[0] * flv[5]) + (im2[1] * flv[6]) + (im2[2] * flv[7]) + (im2[3] * flv[8]) + (im2[4] * flv[9]);
            im2 += dim;
	    r += (im2[0] * flv[10]) + (im2[1] * flv[11]) + (im2[2] * flv[12]) + (im2[3] * flv[13]) + (im2[4] * flv[14]);
            im2 += dim;
	    r += (im2[0] * flv[15]) + (im2[1] * flv[16]) + (im2[2] * flv[17]) + (im2[3] * flv[18]) + (im2[4] * flv[19]);
            im2 += dim;
	    r += (im2[0] * flv[20]) + (im2[1] * flv[21]) + (im2[2] * flv[22]) + (im2[3] * flv[23]) + (im2[4] * flv[24]);
            ds[0] = r;
	    im++;
	    ds++;
        }
        img += dim;
        dst += dim;
    }
}


/*
 * blur - Your current working version of Gaussian blur
 * IMPORTANT: This is the version you will be graded on
 */
char blur_descr[] = "blur: Current working version";
void blur(int dim, float *img, float *flt, float *dst)
{
    blur_2(dim,img,flt,dst);
}

/*********************************************************************
 * register_blur_functions - Register all of your different versions
 *     of the gaussian blur kernel with the driver by calling the
 *     add_blur_function() for each test function. When you run the
 *     driver program, it will test and report the performance of each
 *     registered test function.
 *********************************************************************/

void register_blur_functions()
{
    add_blur_function(&naive_blur, naive_blur_descr);
    add_blur_function(&blur, blur_descr);
    /* ... Register additional test functions here */
}
