#pragma once

#include "CoreMinimal.h"

namespace MiroRandomHelper
{
	template <typename T>
	void ShuffleWithStream(TArray<T>& Array, FRandomStream& Stream)
	{
		const int32 Count = Array.Num();
		for (int32 Index = Count - 1; Index > 0; --Index)
		{
			if (int32 NewIndex = Stream.RandRange(0, Index); Index != NewIndex)
			{
				Array.Swap(Index, NewIndex);
			}
		}
	}
}
