#ifndef ALGORITHM_BASE_HPP
#define ALGORITHM_BASE_HPP

#include<functional>
#include<iterator>
#include<stack>
#define _STD ::std::


template<typename RandomAccessIt , typename Compare>
void _insertion_sort(RandomAccessIt first , RandomAccessIt last , Compare p)
{
	if (last - first < 2)
		return;

	RandomAccessIt now = first + 1;
	for (; now != last; ++now)
	{
		RandomAccessIt temp = now;
		for (; temp != first; --temp)
			if (p(*temp , *(temp - 1)))
				_STD swap(*temp , *(temp - 1));
			else
				break;
	}

}

// FIXME
// 这里的父节点、左右子节点计算中，有奇怪的+1，-1操作，这是因为以1开始计算但是实际表示以0开始导致
// 测试过了，并没有问题

template<typename Dist_type>
inline Dist_type _heap_parent(Dist_type i)
{
	return (i+1)/2 - 1 ;
}

template<typename Dist_type>
inline Dist_type _heap_left(Dist_type i)
{
	return 2 * (i + 1) - 1;
}

template<typename Dist_type>
inline Dist_type _heap_right(Dist_type i)
{
	return 2 * (i + 1);
}

template<typename RandomAccessIt , typename Dist_type , typename Compare>
void _make_heaplfy(RandomAccessIt first , Dist_type size , Dist_type index , Compare p)
{
	for (;;)
	{
		Dist_type left = _heap_left(index);
		Dist_type right = _heap_right(index);
		Dist_type largest = index;
		if (left < size&&p(first [largest] , first [left]))
			largest = left;
		if (right < size&&p(first [largest] , first [right]))
			largest = right;

		if (largest != index)
		{
			_STD swap(first [largest] , first [index]);
			index = largest;
		}
		else
			break;
	}
}

template<typename RandomAccessIt , typename Dist_type , typename Compare>
void _maxheap_sort(RandomAccessIt first , Dist_type dist , Compare p)
{
	for (Dist_type i = dist / 2; i >= 0; --i) // FIXME: 这里有可能可以少一次循环，理由也是从0开始计数，但是多一次肯定不会出错
		_make_heaplfy(first , dist , i , p);

	for (Dist_type i = dist - 1; i != 0; --i)
	{
		_STD swap(first [0] , first [i]);
		_make_heaplfy(first , i , 0 , p);
	}
}

template<typename RandomAccessIt , typename Dist_type , typename Compare>
void _reverse_make_heaplfy(RandomAccessIt rbegin , Dist_type size , Dist_type index , Compare p)
{
	for (;;)
	{
		Dist_type left = 2 * (index + 1) - 1;
		Dist_type right = 2 * (index + 1);
		Dist_type smallest = index;
		if (left < size&&p(rbegin [-left] , rbegin [-smallest]))
			smallest = left;
		if (right < size&&p(rbegin [-right] , rbegin [-smallest]))
			smallest = right;

		if (smallest != index)
		{
			_STD swap(rbegin [-smallest] , rbegin [-index]);
			index = smallest;
		}
		else
			break;
	}
}


template<typename RandomAccessIt , typename Compare>
typename _STD iterator_traits<RandomAccessIt>::difference_type
_heap_test(RandomAccessIt first , RandomAccessIt last , Compare p)
{
	using dist_type = typename _STD iterator_traits<RandomAccessIt>::difference_type;
	dist_type dist = last - first;
	_STD stack<dist_type> sta;
	sta.push(0);
	for (; !sta.empty();)
	{
		dist_type now = sta.top();
		sta.pop();
		dist_type left = _heap_left(now);
		dist_type right = _heap_right(now);
		if (left < dist)
		{
			if (p(first [now] , first [left]))
				return left;
			else
				sta.push(left);
		}
		if (right < dist)
		{
			if (p(first [now] , first [right]))
				return right;
			else
				sta.push(right);
		}
	}
	return dist;
}



#endif // !ALGORITHM_BASE_HPP
