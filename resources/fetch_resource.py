import json
import os
#import urllib3

def main():
    with open('resources/link_sorted.json', "r") as fi:
        resources = json.load(fi)
        print(len(resources))
        with open("aria_list.txt", "w") as fd:
            for resource in reversed(resources):
                #print("{}:{}".format(resource["title"], resource["url"]))
                link = resource["url"]
                fileName = link.rsplit("/", 1)[-1]
                #print(fileName)
                filePath = os.path.join("downloads", fileName)
                #print(filePath)
                if not os.path.isfile(filePath):
                    print("Downloading: {}".format(fileName))
                    fd.write("{}\n".format(link))
                #try:
                    #urllib.request.urlretrieve(link, filePath)
                #except Exception as e:
                #    print(e)
                #    print("Encountered error")


    pass

if __name__ == "__main__":
    main()