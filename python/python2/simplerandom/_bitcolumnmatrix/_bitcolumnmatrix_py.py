
class BitColumnMatrix(object):
    @staticmethod
    def unity(n):
        columns = []
        value = 1
        for _i in range(n):
            columns.append(value)
            value <<= 1
        return BitColumnMatrix(columns)

    @staticmethod
    def mask(n, start, end):
        """Make a BitColumnMatrix that represents a mask.
        BitColumnMatrix size of n*n, to manipulate n binary bits.
        If start <= end, then bits in half-open range [start, end) are set.
        If end < start, then bits in ranges [0, end) and [start, n) are set,
        i.e. bits in range [end, start) are clear; others are set.
        """
        columns = []
        value = 1
        for i in range(n):
            if start <= end:
                columns.append(value if (start <= i < end) else 0)
            else:
                columns.append(value if (start <= i or i < end) else 0)
            value <<= 1
        return BitColumnMatrix(columns)

    @staticmethod
    def shift(n, shift_value):
        columns = []
        if shift_value >= 0:
            value = 1 << shift_value
        else:
            value = 0
        for _i in range(n):
            columns.append(value)
            if shift_value < 0:
                shift_value += 1
                if shift_value == 0:
                    value = 1
            else:
                value <<= 1
                if value >= (1 << n):
                    value = 0
        return BitColumnMatrix(columns)

    def __init__(self, columns, do_copy=True):
        if do_copy:
            self.columns = list(columns)
        else:
            self.columns = columns

    def __add__(self, other):
        if len(self.columns) != len(other):
            raise IndexError("Matrices are not of same width")
        result_columns = []
        for i, column in enumerate(other):
            result_columns.append(self.columns[i] ^ int(column))
        return BitColumnMatrix(result_columns, do_copy=False)

    def __len__(self):
        return len(self.columns)

    def __iter__(self):
        return iter(self.columns)

    def __sub__(self, other):
        return self.__add__(other)

    def __mul__(self, other):
        try:
            other_len = len(other)
        except TypeError:
            # Single value
            x = int(other)
            value = 0
            for column in self.columns:
                if (x & 1):
                    value ^= column
                x >>= 1
            return value
        else:
            # Matrix multiplication
            if len(self.columns) != other_len:
                raise IndexError("Matrices are not of same width")
            result_columns = []
            for other_column in other:
                x = int(other_column)
                value = 0
                for column in self.columns:
                    if (x & 1):
                        value ^= column
                    x >>= 1
                result_columns.append(value)
            return BitColumnMatrix(result_columns, do_copy=False)

    def __imul__(self, other):
        try:
            other_len = len(other)
        except TypeError:
            # Single value. Not suitable for __imul__.
            return NotImplemented
        else:
            # Matrix multiplication
            if len(self.columns) != other_len:
                raise IndexError("Matrices are not of same width")
            result_columns = []
            for other_column in other:
                x = int(other_column)
                value = 0
                for column in self.columns:
                    if (x & 1):
                        value ^= column
                    x >>= 1
                result_columns.append(value)
            self.columns = result_columns
            return self

    def __pow__(self, other):
        n = int(other)
        result = BitColumnMatrix.unity(len(self))
        self_exp = BitColumnMatrix(self.columns)
        while True:
            if n & 1:
                result = self_exp * result
            n >>= 1
            if n == 0:
                break
            self_exp *= self_exp
        return result
