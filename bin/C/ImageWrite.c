
#include "Imogen.h"

typedef struct ImageWrite_t
{
	char filename[1024];
	int format;
	int quality;
}ImageWrite;

int main(ImageWrite *param, Evaluation *evaluation)
{
	char *stockImages[5] = {"Stock/jpg-icon.png", "Stock/png-icon.png", "Stock/tga-icon.png", "Stock/bmp-icon.png", "Stock/hdr-icon.png"};
	Image image;
	
	// set info stock image
	if (ReadImage(stockImages[param->format], &image) == EVAL_OK)
	{
		if (SetEvaluationImage(evaluation->targetIndex, &image) == EVAL_OK)
		{
			FreeImage(&image);
		}
	}
		
	if (!evaluation->forcedDirty)
		return EVAL_OK;
	
	if (GetEvaluationImage(evaluation->inputIndices[0], &image) == EVAL_OK)
	{
		if (WriteImage(param->filename, &image, param->format, param->quality) == EVAL_OK)
		{	
			FreeImage(&image);
			Log("Image %s saved.\n", param->filename);
			return EVAL_OK;
		}
		else
			Log("Unable to write image : %s\n", param->filename);
	}

	return EVAL_ERR;
}