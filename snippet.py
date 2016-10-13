
## Manage snipet for different codes.
import argparse
import pandas as pd
import json

def main():
    snippter_file = "snippet.json"
    parser = argparse.ArgumentParser(description="Snippet Manager")
    parser.add_argument('-s','--snippet',type=str,help="Add snippet",required = False)
    parser.add_argument('-d', '--desc', help="Description of snippet", required=False)
    parser.add_argument('-t','--tags',help="List of tags")
    parser.add_argument('-l','--list',help="List all snippt with given filters")
    args = parser.parse_args()

    ## Error handling will go there

    ## Add to sqlite or csv file. CSV/JSON for now.

    if args.list==False:
        xx=open(snippter_file,"w",encoding="utf-8")
        #js = json.load(open(snippter_file, "w"))
        # Add the snippet
        snippet = args.snippet
        desc = args.desc
        tags = args.tags
        jsdata = {"snippet":snippet,"desc":desc,"tags":tags}
        json.dump(jsdata,xx)
    else:
        js = json.load(open(snippter_file, "r"))
        #List the snippet
        print(js)





if __name__ == '__main__':
    main()
