import json
import datetime

class Resource(dict):
    def __init__(self, title, releaseDate, url):
        self["title"] = title
        val = releaseDate.split("-")
        if len(val) < 3:
            val.append(1)
        date = str(val[0]) + "-" + str(val[1]) + "-" + str(val[2])
        date = datetime.datetime.strptime(date, "%Y-%m-%d").strftime("%Y-%m-%d")#strftime("%d-%m-%Y")
        self["releaseDate"] = date #releaseDate
        self["url"] = url

def main():
    with open("resources/link.txt", "r") as fi:
        resources = []
        for line in fi:
            line = line.strip()
        #while True:
            #line = fi.readline().strip()
            #if not line:
            #    break
            if line.startswith("##") or line == "":
                continue
            else:
                if line.startswith("#"):
                    last = None
                    splits =[]
                    splits = line.split("|")
                    #for s in splits:
                    #    print(s.strip())
                    last = splits
                    next_line = fi.readline().strip()
                    #print(last[1])
                    r = Resource(last[0].split("#")[1].strip(), last[1].strip(), next_line)
                    resources.append(r)
        print(len(resources))
        sorted_resources = sorted(resources, key=lambda x: x["releaseDate"], reverse=True)
        with open("resources/link_sorted.json", "w") as fo:
            json.dump(sorted_resources, fo, indent=1)
        with open("resources/link.json", "w") as fo:
            json.dump(resources, fo, indent=1)
            #print(line)
    #print("Hello")
    #pass

if __name__ == "__main__":
    main()