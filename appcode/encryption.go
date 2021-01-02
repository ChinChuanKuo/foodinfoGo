package appcode

import (
	"crypto/sha256"
	"fmt"
)

func GetEncry256(s string) string {
	return fmt.Sprintf("%x", sha256.Sum256([]byte(s)))
}