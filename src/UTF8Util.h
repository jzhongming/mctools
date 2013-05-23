#include <stdint.h>
#include <vector>
#include <set>
#include <string>
#include <sys/types.h>
#include <stdlib.h>
#include <map>
#include <iostream>
#include <algorithm>
using namespace std;

namespace UTF8UTIL {

#define  MAX_RULE_LEN	9

#define ENCODEONECHAR(ch) \
		(uint16_t)(ch)

#define ENCODETWOCHAR(ch1, ch2) \
		(uint16_t)(((((unsigned char)(ch1))&0x1F)<<6)+(((unsigned char)(ch2))&0x3F))

#define ENCODETHREECHAR(ch1, ch2, ch3) \
		(uint16_t)(((((unsigned char)(ch1))&0x0F)<<12)+((((unsigned char)(ch2))&0x3F)<<6) + (((unsigned char)(ch3))&0x3F))

int getMaxEndOfUtf8(const char *pStr) {
//	size_t wcharCount = 0;
	const char *pBegin = pStr;
	for (; *pStr != '\0';) {
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			pStr++;
		} else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0') {
				return (pStr + 1 - pBegin);
			}
			pStr += 2;
		} else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0') {
				return (pStr + 1 - pBegin);
			}
			pStr += 3;
		} else {
			return (pStr - pBegin);
		}
//
//		if (++wcharCount >= MAX_RULE_LEN) {
//			return (pStr - pBegin);
//		}
	}
	return (pStr - pBegin);
}

int getCharOffset(const char *pStr, int count) {
	const char * pBegin = pStr;
	const char * pOffset = pStr;
	for (; *pStr != '\0';) {
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			pStr++;
			if (count > 0) {
				pOffset++;
			}
		} else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0') {
				return (pOffset - pBegin);
			}
			pStr += 2;
			if (count > 0) {
				pOffset += 2;
			}
		} else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0') {
				return (pOffset - pBegin);
			}
			pStr += 3;
			if (count > 0) {
				pOffset += 3;
			}
		} else {
			return (pOffset - pBegin);
		}
		count--;
	}
	return (pOffset - pBegin);
}

size_t getWordNum(const char *pStr) {
	size_t wordNum = 0;
	for (; *pStr != '\0';) {
		//U-00000000 - U-0000007F: 0xxxxxxx
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			pStr++;
		}
		//U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0')
				return 0;
			pStr += 2;
		}
		//U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0')
				return 0;
			pStr += 3;
		} else {
			return 0;
		}
		wordNum++;
	}
	return wordNum;
}

size_t normalizeString(const char *pStr, uint16_t *pNormalCodes) {
	uint16_t *pValue = pNormalCodes;
	for (; *pStr != '\0';) {
		//U-00000000 - U-0000007F: 0xxxxxxx
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			*pValue++ = (uint16_t)((unsigned char) (*pStr));
			pStr++;
		}
		//U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0')
				return 0;
			*pValue++ = (uint16_t)(
					((((unsigned char) (*pStr)) & 0x1F) << 6)
							+ (((unsigned char) (*(pStr + 1))) & 0x3F));
			pStr += 2;
		}
		//U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0')
				return 0;
			*pValue++ = (uint16_t)(
					((((unsigned char) (*pStr)) & 0x0F) << 12)
							+ ((((unsigned char) (*(pStr + 1))) & 0x3F) << 6)
							+ (((unsigned char) (*(pStr + 2))) & 0x3F));
			pStr += 3;
		} else {
			return 0;
		}
	}
	return pValue - pNormalCodes;
}

size_t normalizeString(const char *pStr, std::vector<uint16_t> &pNormalCodes) {
	for (; *pStr != '\0';) {
		//U-00000000 - U-0000007F: 0xxxxxxx
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			pNormalCodes.push_back((uint16_t)((unsigned char) (*pStr)));
			pStr++;
		}
		//U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0')
				return 0;
			pNormalCodes.push_back(
					(uint16_t)(
							((((unsigned char) (*pStr)) & 0x1F) << 6)
									+ (((unsigned char) (*(pStr + 1))) & 0x3F)));
			pStr += 2;
		}
		//U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0')
				return 0;
			pNormalCodes.push_back(
					(uint16_t)(
							((((unsigned char) (*pStr)) & 0x0F) << 12)
									+ ((((unsigned char) (*(pStr + 1))) & 0x3F)
											<< 6) + (((unsigned char) (*(pStr
									+ 2))) & 0x3F)));
			pStr += 3;
		} else {
			return 0;
		}
	}
	return pNormalCodes.size();
}

//比如str="0xa1 0xb2 0xc3 0xd4 0xe5 0xa6", 则pNormalCodes="1000,1002",那么pPosMatches[0]=3,pPosMatches[1]=6
size_t encodeString(const char *pStr, uint16_t *pNormalCodes,
		size_t *pPosMatches) {
	const char *pStrOri = pStr;
	uint16_t *pValue = pNormalCodes;
	for (; *pStr != '\0';) {
		//U-00000000 - U-0000007F: 0xxxxxxx
		if ((((unsigned char) (*pStr)) & 0x80) == 0) {
			*pValue++ = (uint16_t)((unsigned char) (*pStr));
			pStr++;
			*pPosMatches++ = (pStr - pStrOri);
		}
		//U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
			if (*(pStr + 1) == '\0')
				return 0;
			*pValue++ = (uint16_t)(
					((((unsigned char) (*pStr)) & 0x1F) << 6)
							+ (((unsigned char) (*(pStr + 1))) & 0x3F));
			pStr += 2;
			*pPosMatches++ = (pStr - pStrOri);
		}
		//U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
		else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
			if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0')
				return 0;
			*pValue++ = (uint16_t)(
					((((unsigned char) (*pStr)) & 0x0F) << 12)
							+ ((((unsigned char) (*(pStr + 1))) & 0x3F) << 6)
							+ (((unsigned char) (*(pStr + 2))) & 0x3F));
			pStr += 3;
			*pPosMatches++ = (pStr - pStrOri);
		} else {
			return 0;
		}
	}
	return pValue - pNormalCodes;
}

size_t encodeNext(const char *&pStr, uint16_t &code) {
	if (*pStr == '\0')
		return 0;
	//U-00000000 - U-0000007F: 0xxxxxxx
	if ((((unsigned char) (*pStr)) & 0x80) == 0) {
		code = (uint16_t)((unsigned char) (*pStr));
		pStr++;
		return 1;
	}
	//U-00000080 - U-000007FF: 110xxxxx 10xxxxxx
	else if ((((unsigned char) (*pStr)) & 0xE0) == 0xC0) {
		if (*(pStr + 1) == '\0')
			return 0;
		code = (uint16_t)(
				((((unsigned char) (*pStr)) & 0x1F) << 6)
						+ (((unsigned char) (*(pStr + 1))) & 0x3F));
		pStr += 2;
		return 2;
	}
	//U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx
	else if ((((unsigned char) (*pStr)) & 0xF0) == 0xE0) {
		if (*(pStr + 1) == '\0' || *(pStr + 2) == '\0')
			return 0;
		code = (uint16_t)(
				((((unsigned char) (*pStr)) & 0x0F) << 12)
						+ ((((unsigned char) (*(pStr + 1))) & 0x3F) << 6)
						+ (((unsigned char) (*(pStr + 2))) & 0x3F));
		pStr += 3;
		return 3;
	}
	return 0;
}

}
