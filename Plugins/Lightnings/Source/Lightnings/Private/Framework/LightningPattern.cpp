
#include "Framework/LightningPattern.h"

bool FLightningPattern::FindBranch(int32 JointId, FLightningPattern& OutBranch)
{
	for (FBranchData Branch : Branches)
	{
		if (Branch.JointId == JointId)
		{
			OutBranch = Branch.Pattern;
			return true;
		}
	}
	return false;
}