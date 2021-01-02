package appcode

import (
	"io/ioutil"
	"net"
	"net/http"
	"os"
	"runtime"
	"strings"
)

type InfoObject struct {
	ExternIp string
	InternIp string
	OS       string
	Hostname string
	CPU      int
}

func GetExternIp() string {
	resp, _ := http.Get("http://myexternalip.com/raw")
	defer resp.Body.Close()
	results, _ := ioutil.ReadAll(resp.Body)
	external_ip := strings.Replace(string(results), "\n", "", -1)
	return external_ip
}

func GetInternIp() string {
	conn, _ := net.Dial("udp", "8.8.8.8:80")
	defer conn.Close()
	return strings.Split(conn.LocalAddr().String(), ":")[0]
}

func GetInfoObject() *InfoObject {
	infolist := &InfoObject{OS: runtime.GOOS, CPU: runtime.NumCPU()}
	infolist.ExternIp = GetExternIp()
	infolist.InternIp = GetInternIp()
	infolist.Hostname, _ = os.Hostname()
	return infolist
}

func GetBrowser(userAgent string) string {
	switch strings.Index(userAgent, "Safari") {
	case -1:
		switch strings.Index(userAgent, "Trident") {
		case -1:
			switch strings.Index(userAgent, "Edge") {
			case -1:
				return "FireFox"
			default:
				return "IeEdge"
			}
		default:
			return "IeEdge"
		}
	default:
		return "Safari/Google"
	}
}
